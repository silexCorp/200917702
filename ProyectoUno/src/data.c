#include "data.h"


//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    AREA DE MENSAJES DE ESTADO
/*
 * Mensaje de n */
void mensaje_inicio(){
    /* http://pueblo.sourceforge.net/doc/manual/ansi_color_codes.html */
    printf("\033[%dm",CYAN);
    puts("");
    puts("     ::::::                                                         ::::::");
    puts("     ::     UNIVERSIDAD DE SAN CARLOS - MIA - VACACIONES JUNIO 2016     ::");
    puts("     ::    ALEXANDER MATEO - 200917702 - PRACTICA/PROYECTO PARTE UNO    ::");
    puts("     ::                  INICIANDO SISTEMA DE ARCHIVOS                  ::");
    puts("     :::::::        PARA MOSTRAR MENU DE AYUDA EXCRIBA: help       :::::::");
    puts("                                                                   \033[0m\a\n");
}
/*
 * Mensaje de ayuda */
void mensaje_ayuda(){
    printf("\033[%dm",VERDE);
    puts("     ::::::           AYUDA DISPONIBLE PARA COMANDOS              ::::::");
    printf("     ::     \033[%dmexec -path::dir\033[32m   ejecuta el script                       ::\n",AMARILLO);
    printf("     ::     \033[%dmhelp\033[32m    muestra el menu de ayuda                          ::\n",AMARILLO);
    printf("     ::     \033[%dmclear\033[32m   limpia la pantalla                                ::\n",AMARILLO);
    printf("     ::     \033[%dmmkdisk\033[32m  comando para crear discos                         ::\n",AMARILLO);
    printf("     ::     \033[%dmrmdisk\033[32m  comando para eliminar discos                      ::\n",AMARILLO);
    printf("     ::     \033[%dmfdisk\033[32m   comando para formatear disco                      ::\n",AMARILLO);
    printf("     ::     \033[%dmmount\033[32m   comando para montar disco                         ::\n",AMARILLO);
    printf("     ::     \033[%dmexec\033[32m    comando para ejecutra script                      ::\n",AMARILLO);
    printf("     ::     \033[%dmrep\033[32m     comando para generar reportes                     ::\n",AMARILLO);
    printf("     ::::::::                                                   ::::::::\n");printf("\033[0m\a\n");
}


//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    AREA DE ANALISIS DE COMANDOS
/*
 * Analizar todos los comandos del teclado incluidos los scripts */
void analizar_comandos(){

    char entrada[900];entrada[0] = '\0';
    char palabra[600];palabra[0] = '\0';
    int  tamanio;
    while(fgets (palabra, 600, stdin))
    {
        int cont_ = 0;
        /* Cosas mientras leo líneas */
        limpiar_cadena(palabra); tamanio = get_size(palabra);
        if(tamanio == 0){
            printf("\033[%dmIngrese algún comando\033[0m\a\n",CYAN);
        }else if(strcasecmp(palabra,HELP) == 0){
            mensaje_ayuda();
        }else if(strcasecmp(palabra,EXIT) == 0){
            printf("\033[%dmSaliendo del sistema...\033[0m\a\n",ROJO);
            break;
        }else if(strcasecmp(palabra,CLEAR) == 0){
            system(CLEAR);
            mensaje_inicio();
        }else if(palabra[0] == '#'){
            //Verifica el primer caracter si es #
            //significa que todo lo que viene es
            //comentario y termina con un salto de línea
            printf("\033[%dmComentario encontrado...\033[0m\n",MAGENTA);
        }else if(palabra[tamanio-1] == '\\'){
            for(;cont_ < tamanio-1;cont_++){
                concatenar_char(entrada,palabra[cont_]);
            }
            palabra[0] = '\0';
            printf("    Concatenando: ");
        }else{
            for(;cont_ < tamanio;cont_++){
                concatenar_char(entrada,palabra[cont_]);
            }
            concatenar_char(entrada,'\0');
            /* Comprobar que no venga vacion */
            char *tempo;tempo = malloc(sizeof(entrada)+1);
            strcpy(tempo,entrada);
            char *resultado = strtok (tempo," ");
            if(resultado == NULL){
                printf("                      \033[%dmErr: \033[%dmcomando vacío :p\033[0m\n",ROJO,MAGENTA);
            }else{
                //printf("\"%s\"\n",entrada);
                printf("\033[%dmCADENA LEIDA: \"%s\" \033[%dm(%d)\033[0m\n",AMARILLO,entrada,CYAN, get_size(entrada));
                if(get_size(entrada) > 4){
                    analizar_entrada(entrada);
                }else{
                    err(entrada,"comando muy pequeño");
                }
                entrada[0] = '\0';
            }
        }
    }
}

/*
 * Analizar todos los comandos del archivo de entrada, ejecutando los scripts */
void analizr_script(char *cmd){
    FILE *f = fopen(cmd,"r");
    if(f != NULL){
        inf("Abriendo archivo script...\n");
        char entrada[900];entrada[0] = '\0';
        char palabra[600];palabra[0] = '\0';
        int  tamanio;
        while(fgets(palabra, 600, f) != NULL)/*fscanf(f,"%s\n",cadena) != EOF*/
        {
            int ja = 0;
            if(palabra[0] != '\n'){
                /* Cosas mientras leo líneas */
                limpiar_cadena(palabra); tamanio = get_size(palabra);
                if(tamanio == 0){
                    printf("\033[%dmIngrese algún comando\033[0m\n",CYAN);
                }else if(palabra[0] == '#'){
                    //Verifica el primer caracter si es #
                    //Significa que todo lo que viene es
                    //comentario y termina con un salto de línea
                    printf("\033[%dmComentario encontrado...\033[0m\n",MAGENTA);
                }else if(palabra[tamanio-1] == '\\'){
                    for(;ja < tamanio-1;ja++){
                        //printf("Char: %c\n",palabra[ja]);
                        concatenar_char(entrada,palabra[ja]);
                    }
                    palabra[0] = '\0';
                    printf("    Concatenando: ");
                }else{
                    for(;ja < tamanio;ja++){
                        concatenar_char(entrada,palabra[ja]);
                    }
                    concatenar_char(entrada,'\0');
                    // Comprobar que no venga vacion //
                    char *tempo;tempo = malloc(sizeof(entrada)+1);
                    strcpy(tempo,entrada);
                    char *resultado = strtok (tempo," ");
                    if(resultado == NULL){
                        printf("                      \033[%dmErr: \033[%dmcomando vacío :p\033[0m\n",ROJO,MAGENTA);
                        //return;
                    }else{
                        printf("\033[%dmCADENA LEIDA: \"%s\" \033[%dm(%d)\033[0m\n",AMARILLO,entrada,CYAN, get_size(entrada));
                        if(get_size(entrada) > 4){
                            analizar_entrada(entrada);
                        }else{
                            err(entrada,"comando muy pequeño");
                        }
                        entrada[0] = '\0';
                    }

                }
            }
        }
        fclose(f); //Cerrando archivo
        printf("    Script ejecutado exitosamente...\n");
    }else{
        printf("    Err: archivo \"%s\" (%d) no encontrado.\n",cmd,get_size(cmd));
    }
}


//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    AREA DE VERIFICACIÓN DE COMANDOS
/*
 * Area de analisis y descomposicion de comandos de entrada */
void analizar_entrada(char *entrada){
    int cont = 0, cont1 = 1, tamanio = get_size(entrada), esta = 0, param = 0;
    char temp[600];temp[0] = '\0';
    char *vect[100];
    char cmd[600]; cmd[0] = '\0';
    strcpy(cmd,entrada);
    int evitar_espacios = 1;
    for(;cont <= tamanio;cont++){
        if(cmd[cont] != 0){
            if(param == 0){
                /* Si encuentra un " (parentesis) se queda en ese estado hasta que encuentra el otro " */
                if(cmd[cont] == '#')break;      //puts("Encontro un comentario");
                if(cmd[cont] == '"')param = 1;  //puts("Encontro una comilla");
                if(cmd[cont] != ' '){
                    concatenar_char(temp,cmd[cont]);
                }else{
                    if(cmd[cont-evitar_espacios] == ':'){
                        concatenar_char(temp,cmd[cont]);
                        evitar_espacios++;
                    }else{
                        if(get_size(temp) != 0){
                            vect[esta] = malloc(sizeof(temp)+1);
                            strcpy(vect[esta], temp);
                            esta++;evitar_espacios = 1;
                            temp[0] = '\0';
                        }
                    }
                }
            }else{
                if(cmd[cont] == '"')param = 0;//puts("Encontro una comilla");
                concatenar_char(temp,cmd[cont]);
            }
        }else{
            vect[esta]  = malloc(sizeof(temp)+1);
            strcpy(vect[esta], temp);
            esta++;evitar_espacios = 1;
        }
    }

    /* Quitar los espacios en la palabra que describe el PROCESO */
    quitar_espacio(vect[0], ' ');
    //printf("        SIN SPACE: [%s]\n  ",vect[0]);
    /*
     * Analiza el comando para ESPERAR un enter */
    if(strcasecmp(WAIT,vect[0]) == 0){
        war("esperar...","analizando codigo...");
        getchar();
    }

    /*
     * Analiza el comando para CREAR disco */
    else if(strcasecmp(MKDISK,vect[0]) == 0){
        char r_path[200]; r_path[0] = '\0';
        char r_name[20];  r_name[0] = '\0';
        char r_unit = NULL; int r_size;
        int o_path = 0, o_ta = 0, n_unit = 0, o_na = 0;
        printf("  \033[%dmCREAR DISCO: %s\033[0m\a\n",VERDE,vect[0]);
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0]= final[0]= '\0';
            int tama = get_size(vect[cont]);
            for(;cont1 < 7;cont1++){
                if(cont1 < 5){//NO concat ulitmo "=, : o lo que los separe"
                    concatenar_char(compare,vect[cont][cont1]);
                }
            }
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            //printf("CONCA: %s\n",compare);
            if(strcasecmp(compare, SIZE)==0){
                //printf("SIZE: \'%s\'\n",final);
                r_size = atoi(final);
                if(r_size > 0){
                    o_ta = 1;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\", \'%s\' tipo incompatible!\033[0m\n" ,ROJO,MAGENTA,SIZE,final);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }else if(strcasecmp(compare, PATH)==0){
                //printf("PATH: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_path,final[auxi]);
                        }else{
                            break;
                        }
                    }
                    o_path = 1;
                }else{
                    strcpy(r_path,final);
                    o_path = 1;
                }
            }else if(strcasecmp(compare, UNIT)==0){
                //printf("UNIT: \'%s\'\n",final);
                if(final[0] == 'k' || final[0] == 'K' || final[0] == 'm' || final[0] == 'M'){
                    r_unit = final[0];
                    n_unit = 1;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\", \'%c\' tipo incompatible!\033[0m\n" ,ROJO,MAGENTA,UNIT,final[0]);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }else if(strcasecmp(compare, NAME)==0){
                //printf("NAME: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_name,final[auxi]);
                        }else{
                            break;
                        }
                    }
                    o_na = 1;
                }else{
                    quitar_espacio(final,' ');
                    if(strcmp(final,"") != 0){
                        strcpy(r_name,final);
                        o_na = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verificar si las opcionales estan vacias, las inicializa */
        if(n_unit == 0){
            r_unit = 'M';
        }
        /* Verifica parámetros obligatorios */
        if(o_path == 1 && o_ta == 1 && o_na){
            /* Mandar a CREAR disco */
            //char *pa;pa = malloc(sizeof(400));strcpy(pa,get_path(r_path));//pa=get_path(r_path);
            char *na;na = malloc(sizeof(100));strcpy(na,get_name(r_name));//pa=get_name(r_path);
            printf("  DATA: %s, %s, %c\n",r_path,na,r_unit);
                crear_disco(r_size,r_unit,r_path,na);
            //inf("disco creado exitosamente");
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analiza el comando para REMOVER disco */
    else if(strcasecmp(RMDISK,vect[0]) == 0){
        printf("  \033[%dmELIMINAR DISCO%s\033[0m\a\n",VERDE,vect[0]);
        char r_path[400]; r_path[0] = '\0';
        int o_path = 0;
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0]= final[0]= '\0';
            int tama = get_size(vect[cont]);
            for(;cont1 < 7;cont1++){
                //printf("    CHAR: %c\n",vect[cont][cont1]);
                if(cont1 < 5){//NO concat ulitmo "="
                    concatenar_char(compare,vect[cont][cont1]);
                }
            }
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            //printf("CONCA: %s\n",compare);
            if(strcasecmp(compare, PATH)==0){
                //printf("PATH: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_path,final[auxi]);
                        }else{
                            break;
                        }
                    }
                    o_path = 1;
                }else{
                    strcpy(r_path,final);
                    o_path = 1;
                }
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verifica parámetros obligatorios */
        if(o_path == 1){
            /* Mandar a ELIMINAR disco */
            char *pa;pa = malloc(sizeof(400));strcpy(pa,get_path(r_path));
            char *na;na = malloc(sizeof(100));strcpy(na,get_name(r_path));
            eliminar_disco(pa,na);
            //inf("disco eliminado exitosamente");
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }


    /* Crear particiones con los siguientes parametros
     *
     * SIZE: + valor numérico positivo > 0, si no Err
     * UNIT: - letra para las unidades,
     *              B: bytes,
     *              K: Kilo y
     *              M: Mega, si
     *              NULL usar Kilo, sino != error
     * PATH: + archivo en el que se crea particion, si no existe mostrar error_t
     * TYPE: - indica tipo de partición,
     *              P: primaria,
     *              E: extendida,
     *              L: logica (solo en exten, sin sobrepasar tamaño), si NULL = Priaria
     *         IMPO: la suma de particiones P + E = 4, no se crea lógica sinextendida, si no error_t
     * FIT:  - indica tipo de ajuste en 2o. fase:
     *              BF: Indicara el mejor ajuste (Best Fit)
     *              FF: Utilizara el primer ajuste (First Fit)
     *              WF: Utilizara el peor ajuste (Worst Fit)
     *              NULL usar WF, sino error
     * DELETE -Indicara que se eliminara particion
     *         Se utiliza junto con -NAME y -PATH mostrar mensaje si se eliminó, si no exsites ERR
     *         Si se elimina la EXTENDIDA eliminar las LOGICAS que contenga
     *              Fast: Esta opcion marca como vacio el espacio en la tabal de particiones;
     *              Full: Además de marcar como vaía en la tabla, rellena el espacio con '\0's
     *              sinno error_t
     * NAME:  + Indica el nombre de la particion (no debe repetirse en el disco )
     *          Si se ELIMINA ya debe existir disco, sino mostrar error_t
     *  ADD:  - Se utiliza para AGREGAR o QUITAR espacio de la partición
     *          Puede ser + o - , usara el parametro -UNIT para las unidades a agragar o eliminar
     *          En el caso de agregar espacio, comprobar si existe espacio libre después de la partición,
     *          En el caso de quitar espacio,  comprobar que quiede espacio en la partición (no negativo)
     *
     * Analiza el comando para FORMATEAR disco */
    else if(strcasecmp(FDISK,vect[0]) == 0){
        printf("  \033[%dmCREAR PARTICION: %s\033[0m\a\n",VERDE,vect[0]);
        char r_unit, r_path[450], r_name[20], r_delet[30];
                     r_path[0] =  r_name[0] = r_delet[0] = '\0';
        int  r_size = 0, r_add = 0; char  r_type, r_fit;
        //Para verificar si se ingresaron los parametros obligatorios
        int o_ta = 0, o_path = 0, o_na = 0, n_typ = 0, n_fit = 0, n_del = 0, n_add = 0;
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400]; compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            //printf("TAM: %d\n", tama);
            while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }

            }//Despues concatena el atributo
            contador++;contador++;cont1++;cont1++;
            for(;cont1 < tama;cont1++){
                //printf("    CHAR: %c\n",vect[cont][cont1]);
                concatenar_char(final,vect[cont][cont1]);
            }
            //printf("    DATA: %s,\'%s\'\n",compare,final);
            if(strcasecmp(compare, SIZE)==0){
                //quitar_espacio(final,' ');
                //printf("SIZE: \'%s\'\n",final);
                if(atoi(final) > 0){
                    r_size = atoi(final);
                    o_ta = 1;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\", \'%s\' tamaño incompatible, debe ser mayor que 0\033[0m\n" ,ROJO,MAGENTA,SIZE,final);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }else if(strcasecmp(compare, UNIT)==0){
                //printf("UNIT: \'%s\'\n",final);
                if(final[0] == 'b' || final[0] == 'B'){
                    r_unit = 'B';
                }else if(final[0] == 'k' || final[0] == 'K'){
                    r_unit = 'K';
                }else if(final[0] == 'm' || final[0] == 'M'){
                    r_unit = 'M';
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\", \'%c\' tipo incompatible!\033[0m\n" ,ROJO,MAGENTA,UNIT,final[0]);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }else if(strcasecmp(compare, PATH)==0){
                //printf("PATH: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_path,final[auxi]);
                        }else{
                            break;
                        }
                    }
                    o_path = 1;
                }else{
                    strcpy(r_path,final);
                    o_path = 1;
                }
            }else if(strcasecmp(compare, TYPE)==0){
                //printf("TYPE: \'%s\'\n",final);
                if(final[0] == 'P' || final[0] == 'p'){
                    r_type = 'P';
                    n_typ = 1;
                }else if(final[0] == 'E' || final[0] == 'e'){
                    r_type = 'E';
                    n_typ = 1;
                }else if(final[0] == 'L' || final[0] == 'l'){
                    r_type = 'L';
                    n_typ = 1;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\", \'%s\' tipo incompatible!\033[0m\n" ,ROJO,MAGENTA,TYPE,final);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }else if(strcasecmp(compare, FIT)==0){
                //printf("FIT: \'%s\'\n",final);
                if(final[0] == 'B' || final[0] == 'b'){
                    r_fit = 'B';
                    n_fit = 1;
                }else if(final[0] == 'F' || final[0] == 'f'){
                    r_fit = 'F';
                    n_fit = 1;
                }else if(final[0] == 'W' || final[0] == 'w'){
                    r_fit = 'W';
                    n_fit = 1;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\", \'%s\' tipo incompatible!\033[0m\n" ,ROJO,MAGENTA,FIT,final);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }else if(strcasecmp(compare, DELETE)==0){
                //printf("DELET: \'%s\'\n",final);
                /* Verificar que tipo de particion, nombre a eliminar */
                if(strcasecmp(final,FAST) == 0 || strcasecmp(final,FULL) == 0){
                    strcpy(r_delet,final);
                    n_del = 1;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }else if(strcasecmp(compare, NAME)==0){
                printf("NAME: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_name,final[auxi]);
                            //quitar_espacios_en_blanco(r_name,'_');
                        }else{
                            break;
                        }
                    }
                    o_na = 1;
                }else{
                    quitar_espacio(final,' ');
                    if(strcmp(final,"") != 0){
                        strcpy(r_name,final);
                        o_na = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, ADD)==0){
                //printf("ADD: \'%s\'\n",final);
                r_add = atoi(final);
                n_add = 1;
                /* Verificar si no esta entre comillas */
                if(r_add == 0){
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verificar valores del variables no obligatorias
         * Si existen, si no se inicializa con valor por defecto */
        if(r_unit == 0){
            r_unit = 'K';
        }if(r_type == 0){
            r_type = 'P';
            n_typ = 1;
        }if(r_fit == 0){
            r_fit = 'W';
        }
        /* Verifica parámetros obligatorios para CREAR */
        char *pa;pa = malloc(sizeof(400));strcpy(pa,get_path(r_path));
        char *na;na = malloc(sizeof(100));strcpy(na,get_name(r_path));
        if(o_path == 1 && o_ta == 1 && o_na == 1 && n_del == 0 && n_add == 0){
            /* Mandar a CREAR PARTICION en disco */
            inf("creando partición...");
            //printf("  DATA \n\tPATH: '%s\' \n\tNAME: \'%s\' \n\tSIZE: \'%d\' \n\tUNIT: \'%c\' \n\tTYPE: \'%c\' \n\tFIT: \'%c\' \n\tpNAME: \'%s\' \n",pa,na,r_size,r_unit,r_type,r_fit,r_name);
            crear_particion(r_path,r_size,r_unit,r_type,r_fit,r_name);

        }else if(o_path == 1 && o_na == 1){
            if(n_del == 1){//Usa: name y path : type full o fast
                inf("eliminando particion...");
                printf("  DATA \n\tPATH: '%s\' \n\tNAME: \'%s\' \n\tDELTE: \'%s\' \n\tpNAME: \'%s\' \n",pa,na,r_delet,r_name);
                eliminar_particion(r_path,r_name, r_delet);
            }else if(n_add == 1){
                //inf("agregando/quitanso espacio...");
                printf("  DATA \n\tPATH: '%s\' \n\tNAME: \'%s\' \n\tUNIT: \'%c\' \n\tADD: \'%d\' \n\tpNAME: \'%s\' \n",pa,na,r_unit,r_add,r_name);
                if(r_add < 0){
                    int espacio = r_add*-1;
                    inf("eliminando espacio en particion...");
                    eliminar_espacio_particion(r_path,r_name,r_unit,espacio);
                }else{
                    inf("agregando espacio en particion...");
                    agregar_espacio_particion(r_path,r_name,r_unit,r_add);
                }
            }
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analiza el comando para MONTAR disco */
    else if(strcasecmp(MOUNT,vect[0]) == 0){
        printf("  \033[%dmMONTAR DISCO: %s\033[0m\a\n",VERDE,vect[0]);
        char r_path[450], r_name[20];
             r_path[0] =  r_name[0] = '\0';
        //Para verificar si se ingresaron los parametros obligatorios
        int o_path = 0, o_na = 0;
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }

            }//Despues concatena el atributo
            contador++;contador++;cont1++;cont1++;
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            //printf("    DATA: %s,\'%s\'\n",compare,final);
            if(strcasecmp(compare, PATH)==0){
                //printf("PATH: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_path,final[auxi]);
                        }else{
                            break;
                        }
                    }
                    o_path = 1;
                }else{
                    strcpy(r_path,final);
                    o_path = 1;
                }
            }else if(strcasecmp(compare, NAME)==0){
                //printf("NAME: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_name,final[auxi]);
                        }else{
                            break;
                        }
                    }
                    o_na = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_name,final);
                        o_na = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                    //strcpy(r_path,final);
                    //o_path = 1;
                }
            }else{
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
        }

        /* Verifica parámetros obligatorios para CREAR */
        if(o_path == 1 && o_na == 1){
            /* Mandar a MONTAR particion */
            //char *pa;pa = malloc(sizeof(400));strcpy(pa,get_path(r_path));//pa=get_path(r_path);
            //char *na;na = malloc(sizeof(100));strcpy(na,get_name(r_path));//pa=get_name(r_path);
            exe(r_path,"montando partición");
            montar_particion(r_path,r_name);
            //printf("DATA path: \'%s\' name: \'%s\'\n",pa,na);
        }else{
            inf("   PARTICIONES MONTADAS");
            mostrar_particiones_montadas();
            //printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analiza el comando para DESMONTAR disco */
    else if(strcasecmp(UMOUNT,vect[0]) == 0){
        printf("  \033[%dmDESMONTAR DISCO: %s\033[0m\a\n",VERDE,vect[0]);
        char r_id[20];
             r_id[0] = '\0';
        //Para verificar si se ingresaron los parametros obligatorios
        int o_id = 0;
        char *arr[30];
        for(cont = 1;cont < esta; cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }

            }//Despues concatena el atributo
            contador++;contador++;cont1++;cont1++;
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }



            //printf("    DATA: %s,\'%s\'\n",compare,final);
            if(ID[0]== vect[cont][1] || ID[0]==vect[cont][1] || ID[1]==vect[cont][2] || ID[1]==vect[cont][2]){
                printf("ID: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_id,final[auxi]);
                        }else{
                            o_id = 1;
                            break;
                        }
                    }
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_id,final);
                        o_id = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else{
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }

        /* Verifica parámetros obligatorios para CREAR */
        if(o_id == 1){
            desmontar_particion(r_id);
            //inf("particion desmontada exitosamente");
            //printf("    SUCCESS UNMOUNT: \'%s\'\n",r_id);
        }else{
            inf("   PARTICIONES DESMONTADAS");
            mostrar_particiones_desmontadas();
            //printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analiza el comando para DISK FREE */
    else if(strcasecmp(DF,vect[0]) == 0){
        int o_k = 0, o_m = 0, o_h = 0, o_i = 0;
        printf("  \033[%dmDISK FREE: %s\033[0m\a\n",VERDE,vect[0]);
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0]= final[0]= '\0';
            int tama = get_size(vect[cont]);
            for(;cont1 < 7;cont1++){
                if(cont1 < 5){//NO concat ulitmo "=, : o lo que los separe"
                    concatenar_char(compare,vect[cont][cont1]);
                }
            }
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            printf("FREE: %s\n",compare);
            if(strcasecmp(compare, "K")==0){
                o_k = 1;
            }else if(strcasecmp(compare, "M")==0){
                o_m = 1;
            }else if(strcasecmp(compare, "H")==0){
                o_h = 1;
            }else if(strcasecmp(compare, "I")==0){
                o_i = 1;
            }else{
                printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                final[0] = compare[0] = '\0';
                tama = 0;cont1 = 1; //Reinicializar parámetros
                return;

            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verifica parámetros obligatorios */
        if(1){
            printf("  DATA:  %d, %d, %d, %d (k,m,h,i)\n",o_k,o_m,o_h,o_i);
            //#    crear_disco(r_size,r_unit,pa,na);
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analiza el comando para DISK USED */
    else if(strcasecmp(DU,vect[0]) == 0){
        int r_size;
        char r_path[200]; r_path[0] = '\0';
        int o_h = 0, o_n = 0, o_path=0, car = 0;
        printf("  \033[%dmDISCO USADO: %s\033[0m\a\n",VERDE,vect[0]);
        //Para verificar si se ingresaron los parametros obligatorios
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                //printf("CHAR: %c\n",vect[cont][cont1]);
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    //printf("CHAR: %d,%c\n",cont1,vect[cont][cont1]);
                    if(vect[cont][1] != 'p'){
                        //printf(" COMP: %c,%c\n",vect[cont][1],vect[cont][cont1]);
                        if(((vect[cont][cont1] == 'h' ) ||
                            (vect[cont][cont1] == 'H' )) && car == 0){
                            car = 1;
                            //cont1++;contador++;
                            break;
                        }
                    }
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }

            }//Despues concatena el atributo
            if(car == 1){
                //puts("EEEEES CARACTER");
                o_h = 1;
                car = 2;
            }else{
                contador++;contador++;cont1++;cont1++;
                for(;cont1 < tama;cont1++){
                    concatenar_char(final,vect[cont][cont1]);
                }


                /*
                if(vect[cont][0]=='n' || compare[0]=='N'){
                    char *temp = malloc(sizeof(compare)+1);
                    strcpy(temp,compare);
                    compare[0] = final[0] = '\0';
                    strcpy(compare,"n");
                    //final = malloc(sizeof(compare)+1);
                    int a = 3;
                    for(;a < sizeof(compare)+1; a++){
                        concatenar_char(final,compare[a]);
                    }
                    puts("ES UNAS FSDASFSD");

                }*/


                //printf("    DATA(: %s,\'%s\'\n",compare,final);
                if(strcasecmp(compare, PATH)==0){
                    //printf("PATH: \'%s\'\n",final);
                    // Verificar si no esta entre comillas //
                    if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                        for(;auxi < end;auxi++){
                            if(final[auxi] != '"'){
                                concatenar_char(r_path,final[auxi]);
                            }else{
                                break;
                            }
                        }
                        o_path = 1;
                    }else{
                        strcpy(r_path,final);
                        o_path = 1;
                    }
                }else if(strcasecmp(compare, "N")==0){
                    //printf("N: \'%s\'\n",final);
                    if(atoi(final) > 0){
                        r_size = atoi(final);
                         o_n = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\", \'%s\' tamaño incompatible, debe ser mayor que 0\033[0m\n" ,ROJO,MAGENTA,SIZE,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }else{
                    if(compare[0] == 0){
                        //Ignorara
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        //return;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
                final[0] = compare[0] = '\0';
                tama = 0;cont1 = 1; //Reinicializar parámetros

            }


        }

        /* Verifica parámetros obligatorios */
        if(o_h == 1){
            printf("  DATA H Ok: %d\n",o_h);
            if(o_n == 1 || o_path == 1){
                printf("  Final Ok, N: %d, Path: %s\n",r_size, r_path);
                //#    crear_disco(r_size,r_unit,pa,na);
            }
            //#    crear_disco(r_size,r_unit,pa,na);
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analiza el comando REP para buscar archivo o carpeta */
    else if(strcasecmp(REP,vect[0]) == 0){
        printf("    \033[%dmGENERAR REPORTE: %s\033[0m\a\n",VERDE,vect[0]);
        char r_id[10], r_path[200], r_name[10], r_ruta[200];
             r_id[0] = r_path[0] =  r_name[0] = r_ruta[0] = '\0';
        //Para verificar si se ingresaron los parametros obligatorios
        int o_id = 0, o_path = 0, o_name = 0, n_ruta = 0;
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }
            }//Despues concatena el atributo
            contador++;contador++;cont1++;cont1++;
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            if(strcasecmp(compare, NAME)==0){
                //printf("CONT: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_name,final[auxi]);
                        }else{
                            break;
                        }
                    }
                    //o_name = 1;
                }else{
                    strcpy(r_name,final);
                    //o_name = 1;
                }
                if(strcasecmp(r_name,BM_INODE) == 0 || strcasecmp(r_name,BM_BLOCK) == 0 ||
                   strcasecmp(r_name,INODE) == 0   || strcasecmp(r_name,BLOCK) == 0 ||
                   strcasecmp(r_name,TREE) == 0  || strcasecmp(r_name,SB) == 0    ||
                   strcasecmp(r_name,FFILE) == 0    || strcasecmp(r_name,JOURNALING) == 0 ||
                   strcasecmp(r_name,LS) == 0    || strcasecmp(r_name,LS) == 0 ||
                   strcasecmp(r_name,DDISK) == 0  || strcasecmp(r_name,MMBR) == 0 ){
                    o_name = 1;
                }else{
                    printf("                    \033[%dmErr: \033[%dmen parametro \"%s\", valor incompatible \033[0m\n" ,ROJO,MAGENTA,final);
                    final[0] = compare[0] = '\0';
                    return;
                }
            }else if(strcasecmp(compare, PATH)==0){
                //printf("PATH: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_path,final[auxi]);
                        }else{
                            break;
                        }
                    }
                    o_path = 1;
                }else{
                    strcpy(r_path,final);
                    o_path = 1;
                }
            }else if(strcasecmp(compare, ID)==0){
                //printf("ID: \'%s\'\n",final);
                int exceso = 0;
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            exceso++;
                            if(exceso <= 10){
                                concatenar_char(r_id,final[auxi]);
                            }else{
                                printf("                    \033[%dmErr: \033[%dmen parametro \"%s\" el tamaño excede de 10\033[0m\n" ,ROJO,MAGENTA,final);
                                final[0] = compare[0] = '\0';
                                return;
                            }
                        }else{
                            break;
                        }
                    }
                    o_id = 1;
                }else{
                    if(get_size(final) <= 10){
                        strcpy(r_id,final);
                        o_id = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmen parametro \"%s\" el tamaño excede de 10\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        return;
                    }
                }
            }else if(strcasecmp(compare, RUTA)==0){
                //printf("CONT: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_ruta,final[auxi]);
                        }else{
                            break;
                        }
                    }
                    n_ruta = 1;
                }else{
                    strcpy(r_ruta,final);
                    n_ruta = 1;
                }
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }

        /* Verifica parámetros obligatorios para REMOVER */
        if(o_id == 1 && o_path == 1 && o_name == 1){
            /* Mandar a CREAR PARTICION en disco */

            //printf("PATHOOOOOO: %s\n", r_path);
            //char *pa;pa = malloc(sizeof(r_path));strcpy(pa,get_path(r_path));
            //printf("PATHHHHHHH: %s\n", pa);
            //crear_carpeta(pa);
            //char *na;na = malloc(sizeof(100));strcpy(na,get_name(r_path));
            //char *ex;ex = malloc(sizeof(100));strcpy(ex,get_ext(r_path));
            if(strcasecmp(r_name,DDISK)==0){
                Reporte_Disco(r_id,r_path,r_name);
                //generar_reporte_disco(pa,na,ex,r_id);
            }else if(strcasecmp(r_name,MMBR)==0){
                Reporte_MBR_EBR(r_id,r_path,r_name);
                //generar_reporte_mbr(pa,na,ex,r_id);
            }
            /*else if(strcasecmp(r_name,SB)==0){
                buscando_super_bloque(r_id,r_path);
            }else if(strcasecmp(r_name,TREE)==0){
                buscar_bitmaps(r_id,r_path, TREE);
            }else if(strcasecmp(r_name,FFILE)==0){
                buscar_bitmaps(r_id,r_path, FFILE);
            }else if(strcasecmp(r_name,JOURNALING)==0){
                buscar_bitmaps(r_id,r_path, JOURNALING);
            }else if(strcasecmp(r_name,BM_INODE)==0){
                buscar_bitmaps(r_id,r_path, BM_INODE);
            }else if(strcasecmp(r_name,BM_BLOCK)==0){
                buscar_bitmaps(r_id,r_path, BM_BLOCK);
            }else if(strcasecmp(r_name,LS)==0){
                buscar_carpetas(r_id,r_path);
            }*/
            /*else if(strcasecmp(r_name,BLOCK)==0){
                generar_reporte_mbr(pa,na,ex,r_id);
            }else if(strcasecmp(r_name,BM_BLOCK)==0){
                generar_reporte_mbr(pa,na,ex,r_id);
            }else if(strcasecmp(r_name,TREE)==0){
                generar_reporte_mbr(pa,na,ex,r_id);
            }else if(strcasecmp(r_name,FFILE)==0){
                generar_reporte_mbr(pa,na,ex,r_id);
            }else if(strcasecmp(r_name,LS)==0){
                generar_reporte_mbr(pa,na,ex,r_id);
            }*/
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analiza el comando para EJECUTAR script */
    else if(strcasecmp(EXEC,vect[0]) == 0){
        printf("  \033[%dmCARGAR SCRIPT: %s\033[0m\a\n",VERDE,vect[0]);
        char r_path[450];
             r_path[0] = '\0';
        //Para verificar si se ingresaron los parametros obligatorios
        int o_path = 0;
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            while(1){//Concatena todo lo que viene entre '-' y ':' ejemplo: - 'size' :
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }

            }//Despues concatena el atributo
            contador++;contador++;cont1++;cont1++;
            /*for(;cont1 < contador;cont1++){
                //printf("    CHAR: %c\n",vect[cont][cont1]);
                if(cont1 < 5){//NO concat ulitmo "="
                    concatenar_char(compare,vect[cont][cont1]);
                }
            }*/
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            //printf("    DATA: %s,\'%s\'\n",compare,final);
            if(strcasecmp(compare, PATH)==0){
                //printf("PATH: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_path,final[auxi]);
                        }else{
                            break;
                        }
                    }
                    o_path = 1;
                }else{
                    strcpy(r_path,final);
                    o_path = 1;
                }
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }

        /* Verifica parámetros obligatorios para CREAR */
        if(o_path == 1){
            //crear_reporte(r_path,a_name,r_ext,r_id,r_name);
            printf("    SUCCESS EXEC: '%s\'\n",r_path);
            analizr_script(r_path);
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }

    }





    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    AREA DE VERIFICACIÓN DE COMANDOS
    /*
     * Area de analisis y descomposicion de las entradas */
    /*
     * Analizador de la SEGUNDA FASE con los siguientes parametros */
    else if(strcasecmp(MKFS,vect[0]) == 0){
        printf("  \033[%dmFORMATEO DE PARTICION: %s\033[0m\a\n",VERDE,vect[0]);

        char r_fs[30], r_type[30], r_id[30], r_unit;
             r_fs[0] = r_type[0] = r_id[0] = '\0';
        int  r_add = 0;
        //Para verificar si se ingresaron los parametros obligatorios
        int o_id = 0, n_fs = 1, n_typ = 0, n_uni = 0, n_add = 0;
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }

            }//Despues concatena el atributo
            contador++;contador++;cont1++;cont1++;
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            //printf("    DATA: %s,\'%s\'\n",compare,final);
            if(strcasecmp(compare, FS)==0){
                //printf("PATH: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_fs,final[auxi]);
                        }else{
                            break;
                        }
                    }
                    n_fs = 0; //0 = 3xt2, 1 = ext3
                }else{
                    strcpy(r_fs,final);
                    n_fs = 0;
                }
            }else if(strcasecmp(compare, ID)==0 || strcasecmp(compare, NAME)==0){
                //NAME: indicará el id que se generó con el comando mount de la primera fase
                printf("ID: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_id,final[auxi]);
                        }else{
                            o_id = 1;
                            break;
                        }
                    }
                    o_id = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_id,final);
                        o_id = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, TYPE)==0){
                printf("TYPE: \'%s\'\n",final);
                if(strcasecmp(final, FULL)==0 || strcasecmp(final, FAST)==0){
                    strcpy(r_type,final);
                    //r_type = final[0];
                    n_typ = 1;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\", \'%s\' tipo incompatible!\033[0m\n" ,ROJO,MAGENTA,TYPE,final);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }else if(strcasecmp(compare, ADD)==0){
                printf("ADD: \'%s\'\n",final);
                r_add = atoi(final);
                n_add = 1;
                /* Verificar si no esta entre comillas */
                if(r_add == 0){
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" se agrega 0!\033[0m\n" ,ROJO,MAGENTA,final);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }else if(strcasecmp(compare, UNIT)==0){
                printf("UNIT: \'%s\'\n",final);
                if(final[0] == 'b' || final[0] == 'B' || final[0] == 'k' || final[0] == 'K' || final[0] == 'm' || final[0] == 'M'){
                    r_unit = final[0];
                    n_uni = 1;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\", \'%c\' tipo incompatible!\033[0m\n" ,ROJO,MAGENTA,UNIT,final[0]);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verificar valores del variables no obligatorias
         * Si existen, si no se inicializa con valor por defecto */
        if(r_unit == 0){
            r_unit = 'K';
            n_uni = 1;
        }if(r_type[0] == 0){
            strcpy(r_type,"FULL");
            n_typ = 1;
        }

        /* Verifica parámetros obligatorios para CREAR */
        if(o_id == 1){
            //#    formatear_particion(r_id, r_type);
            //mkfs_disco(r_id,r_type,r_add,r_unit);
            //crear_reporte(r_path,a_name,r_ext,r_id,r_name);
            printf("    SUCCESS MKFS: [%s] %d,\'%s\',%s,%c\n",r_fs,r_add,r_id,r_type,r_unit);
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analizador de la SEGUNDA FASE con LOGIN */
    else if(strcasecmp(LOGIN,vect[0]) == 0){
        printf("  \033[%dmINICIAR SESION: %s\033[0m\a\n",VERDE,vect[0]);

        char r_usr[300], r_pwd[300];
             r_usr[0] =  r_pwd[0] = '\0';
        int  o_usr = 0, o_pwd = 0;
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }

            }//Despues concatena el atributo
            contador++;contador++;cont1++;cont1++;
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            //printf("    DATA: %s,\'%s\'\n",compare,final);
            if(strcasecmp(compare, USR)==0){
                //USR: indicará el id que se generó con el comando mount de la primera fase
                printf("USR: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_usr,final[auxi]);
                        }else{
                            o_usr = 1;
                            break;
                        }
                    }
                    o_usr = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_usr,final);
                        o_usr = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, PWD)==0){
                //PWD: indicará el id que se generó con el comando mount de la primera fase
                printf("PWD: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_pwd,final[auxi]);
                        }else{
                            o_pwd = 1;
                            break;
                        }
                    }
                    o_pwd = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_pwd,final);
                        o_pwd = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verificar valores del variables no obligatorias
         * Si existen, si no se inicializa con valor por defecto */

        /* Verifica parámetros obligatorios para INICIAR SESION */
        if(o_usr == 1 && o_pwd == 1){
            if(get_size(r_usr) < 10 && get_size(r_pwd) < 10 ){
                //crear_reporte(r_path,a_name,r_ext,r_id,r_name);
                printf("    LOGIN SUCCESS: [%s] %s\n",r_usr,r_pwd);
            }else{
                printf("                    \033[%dmErr: \033[%dmen los parametros, exceden el tamaño \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
                return;
            }
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analizador de la SEGUNDA FASE con LOGOUT */
    else if(strcasecmp(LOGOUT,vect[0]) == 0){
        printf("  \033[%dmCERRAR SESION: %s\033[0m\a\n",VERDE,vect[0]);
        int o_login = 1;
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }

            }//Despues concatena el atributo
            contador++;contador++;cont1++;cont1++;
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verificar valores del variables no obligatorias
         * Si existen, si no se inicializa con valor por defecto */

        /* Verifica parámetros obligatorios para INICIAR SESION */
        if(o_login == 1){
            //crear_reporte(r_path,a_name,r_ext,r_id,r_name);
            printf("    LOGIN SUCCESS: :)\n");
        }else{
            printf("                    \033[%dmErr: \033[%dmcesión iniciada: \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analizador de la SEGUNDA FASE con MKGRP */
    else if(strcasecmp(MKGRP,vect[0]) == 0){
        printf("  \033[%dmCREAR GRUPO: %s\033[0m\a\n",VERDE,vect[0]);

        char r_name[300], r_id[300];
             r_name[0] =  r_id[0] = '\0';
        int  o_name = 0, o_id = 0;
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }

            }//Despues concatena el atributo
            contador++;contador++;cont1++;cont1++;
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            //printf("    DATA: %s,\'%s\'\n",compare,final);
            if(strcasecmp(compare, NAME)==0){
                //PWD: indicará el id que se generó con el comando mount de la primera fase
                printf("NAME: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_name,final[auxi]);
                        }else{
                            o_name = 1;
                            break;
                        }
                    }
                    o_name = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_name,final);
                        o_name = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, ID)==0){
                //PWD: indicará el id que se generó con el comando mount de la primera fase
                printf("ID: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_id,final[auxi]);
                        }else{
                            o_id = 1;
                            break;
                        }
                    }
                    o_id = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_id,final);
                        o_id = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verificar valores del variables no obligatorias
         * Si existen, si no se inicializa con valor por defecto */

        /* Verifica parámetros obligatorios para INICIAR SESION */
        if(o_id == 1 && o_name == 1){
            if(get_size(r_id) < 10 && get_size(r_name) < 10 ){
                //crear_reporte(r_path,a_name,r_ext,r_id,r_name);
                printf("    MAKE GROUP SUCCESS: [%s] %s\n",r_id,r_name);
            }else{
                printf("                    \033[%dmErr: \033[%dmen los parametros, exceden el tamaño \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
                return;
            }
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analizador de la SEGUNDA FASE con MKGRP */
    else if(strcasecmp(RMGRP,vect[0]) == 0){
        printf("  \033[%dmREMOVER GRUPO: %s\033[0m\a\n",VERDE,vect[0]);

        char r_name[300], r_id[300];
             r_name[0] =  r_id[0] = '\0';
        int  o_name = 0, o_id = 0;
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }

            }//Despues concatena el atributo
            contador++;contador++;cont1++;cont1++;
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            //printf("    DATA: %s,\'%s\'\n",compare,final);
            if(strcasecmp(compare, NAME)==0){
                //PWD: indicará el id que se generó con el comando mount de la primera fase
                printf("NAME: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_name,final[auxi]);
                        }else{
                            o_name = 1;
                            break;
                        }
                    }
                    o_name = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_name,final);
                        o_name = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, ID)==0){
                //PWD: indicará el id que se generó con el comando mount de la primera fase
                printf("ID: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_id,final[auxi]);
                        }else{
                            o_id = 1;
                            break;
                        }
                    }
                    o_id = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_id,final);
                        o_id = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verificar valores del variables no obligatorias
         * Si existen, si no se inicializa con valor por defecto */

        /* Verifica parámetros obligatorios para INICIAR SESION */
        if(o_id == 1 && o_name == 1){
            if(get_size(r_id) < 10 && get_size(r_name) < 10 ){
                //crear_reporte(r_path,a_name,r_ext,r_id,r_name);
                printf("    GROUP REMOVED SUCCESS: [%s] %s\n",r_id,r_name);
            }else{
                printf("                    \033[%dmErr: \033[%dmen los parametros, exceden el tamaño \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
                return;
            }

        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analizador de la SEGUNDA FASE con MKUSR */
    else if(strcasecmp(MKUSR,vect[0]) == 0){
        printf("  \033[%dmCREAR USUARIO: %s\033[0m\a\n",VERDE,vect[0]);

        char r_usr[300], r_id[300], r_pwd[300], r_grp[300];
             r_usr[0] =  r_id[0] =  r_pwd[0] =  r_grp[0] = '\0';
        int  o_usr = 0,  o_id = 0,  o_pwd = 0,  o_grp = 0;
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }

            }//Despues concatena el atributo
            contador++;contador++;cont1++;cont1++;
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            //printf("    DATA: %s,\'%s\'\n",compare,final);
            if(strcasecmp(compare, USR)==0){
                //USR: indicará el id que se generó con el comando mount de la primera fase
                printf("USR: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_usr,final[auxi]);
                        }else{
                            o_usr = 1;
                            break;
                        }
                    }
                    o_usr = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_usr,final);
                        o_usr = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, ID)==0){
                //ID: indicará el id que se generó con el comando mount de la primera fase
                printf("ID: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_id,final[auxi]);
                        }else{
                            o_id = 1;
                            break;
                        }
                    }
                    o_id = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_id,final);
                        o_id = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, PWD)==0){
                //PWD: indicará el id que se generó con el comando mount de la primera fase
                printf("PWD: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_pwd,final[auxi]);
                        }else{
                            o_pwd = 1;
                            break;
                        }
                    }
                    o_pwd = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_pwd,final);
                        o_pwd = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, GRP)==0){
                //GRP: indicará el id que se generó con el comando mount de la primera fase
                printf("GRP: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_grp,final[auxi]);
                        }else{
                            o_grp = 1;
                            break;
                        }
                    }
                    o_grp = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_grp,final);
                        o_grp = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verificar valores del variables no obligatorias
         * Si existen, si no se inicializa con valor por defecto */

        /* Verifica parámetros obligatorios para INICIAR SESION */
        if(o_usr == 1 && o_id == 1 && o_pwd == 1 && o_grp == 1){
            if(get_size(r_usr) < 10 && get_size(r_id) < 10 && get_size(r_pwd) < 10 && get_size(r_grp) < 10){
                //crear_reporte(r_path,a_name,r_ext,r_id,r_name);
                printf("    USER CREATED: [%s] %s\n",r_id,r_usr);
            }else{
                printf("                    \033[%dmErr: \033[%dmen los parametros, exceden el tamaño \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
                return;
            }
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analizador de la SEGUNDA FASE con MKUSR */
    else if(strcasecmp(RMUSR,vect[0]) == 0){
        printf("  \033[%dmCREAR USUARIO: %s\033[0m\a\n",VERDE,vect[0]);

        char r_usr[300], r_id[300];
             r_usr[0] =  r_id[0] = '\0';
        int  o_usr = 0,  o_id = 0;
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }

            }//Despues concatena el atributo
            contador++;contador++;cont1++;cont1++;
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            //printf("    DATA: %s,\'%s\'\n",compare,final);
            if(strcasecmp(compare, USR)==0){
                //USR: indicará el id que se generó con el comando mount de la primera fase
                printf("USR: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_usr,final[auxi]);
                        }else{
                            o_usr = 1;
                            break;
                        }
                    }
                    o_usr = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_usr,final);
                        o_usr = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, ID)==0){
                //ID: indicará el id que se generó con el comando mount de la primera fase
                printf("ID: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_id,final[auxi]);
                        }else{
                            o_id = 1;
                            break;
                        }
                    }
                    o_id = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_id,final);
                        o_id = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verificar valores del variables no obligatorias
         * Si existen, si no se inicializa con valor por defecto */

        /* Verifica parámetros obligatorios para INICIAR SESION */
        if(o_usr == 1 && o_id == 1){
            if(get_size(r_usr) < 10 && get_size(r_id)){
                //crear_reporte(r_path,a_name,r_ext,r_id,r_name);
                printf("    USER DELETED: [%s] %s\n",r_id,r_usr);
            }else{
                printf("                    \033[%dmErr: \033[%dmen los parametros, exceden el tamaño \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
                return;
            }
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analiza el comando para PERMISOS */
    else if(strcasecmp(CHMOD,vect[0]) == 0){
        char r_path[200]; r_path[0] = '\0';
        char r_id[200]; r_id[0] = '\0';
        int r_ugo = 0, o_ugo = 0, o_id = 0, o_path = 0, r_rec = 0;
        printf("  \033[%dmPERMISOS: %s\033[0m\a\n",VERDE,vect[0]);
        //Para verificar si se ingresaron los parametros obligatorios
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                //printf("CHAR: %c\n",vect[cont][cont1]);
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    //printf("CHAR: %d,%c\n",cont1,vect[cont][cont1]);
                    /*if(vect[cont][1] != 'R' || vect[cont][1] != 'r'){
                        //printf(" COMP: %c,%c\n",vect[cont][1],vect[cont][cont1]);
                        if(((vect[cont][cont1] == 'h' ) ||
                            (vect[cont][cont1] == 'H' )) && car == 0){
                            r_rec = 1;
                            //cont1++;contador++;
                            break;
                        }
                    }*/
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }

            }//Despues concatena el atributo
            contador++;contador++;cont1++;cont1++;
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            //printf("    DATA(: %s,\'%s\'\n",compare,final);
            if(strcasecmp(compare, PATH)==0){
                //printf("PATH: \'%s\'\n",final);
                // Verificar si no esta entre comillas //
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_path,final[auxi]);
                        }else{
                            break;
                        }
                    }
                    o_path = 1;
                }else{
                    strcpy(r_path,final);
                    o_path = 1;
                }
            }else if(strcasecmp(compare, ID)==0){
                //printf("ID: \'%s\'\n",final);
                // Verificar si no esta entre comillas //
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_path,final[auxi]);
                        }else{
                            break;
                        }
                    }
                    o_id = 1;
                }else{
                    strcpy(r_id,final);
                    o_id = 1;
                }
            }else if(strcasecmp(compare, UGO)==0){
                printf("UGO: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] >= 48 && final[0] <= 55 && final[1] >= 48 && final[1] <= 55 && final[2] >= 48 && final[2] <= 55){
                    r_ugo = atoi(final);
                    o_ugo = 1;
                    if(r_ugo < 0){
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" se agrega un negativo!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, "R")==0){
                printf("R: \'%s\'\n",final);
                r_rec = 1;
                /*if(atoi(final) > 0){
                    r_size = atoi(final);
                     o_n = 1;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\", \'%s\' tamaño incompatible, debe ser mayor que 0\033[0m\n" ,ROJO,MAGENTA,SIZE,final);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }*/
            }else{
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
        }

        /* Verifica parámetros obligatorios */
        if(o_ugo == 1 && o_id == 1 && o_path == 1){
            printf("  Final Ok, R: %d, Path: %s, Id: %s, Ugo: %d\n",r_rec, r_path, r_id, r_ugo);
            //#    crear_disco(r_size,r_unit,pa,na);
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analiza el comando MKFILE para crear archivos */
    else if(strcasecmp(MKFILE,vect[0]) == 0){

        printf("  \033[%dmCREAR ARCHIVO: %s\033[0m\a\n",VERDE,vect[0]);
        char r_id[10], r_path[200], r_cont[200];
             r_id[0] = r_path[0] =  r_cont[0] = '\0';
        //Para verificar si se ingresaron los parametros obligatorios
        int r_p = 0, r_size = 0, o_id = 0, o_path = 0, n_size = 0, n_cont = 0;

        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0, aux = 0;
            //printf("Tam: %s - %d,%d\n",vect[cont],get_size(vect[cont]), cont1+1);
            if(get_size(vect[cont]) > cont1+1){
                if(vect[cont][cont1] == 'p' || vect[cont][cont1] == 'P'){
                    if(vect[cont][cont1+1] != 'a' || vect[cont][cont1+1] != 'A'){
                        while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                            if(vect[cont][cont1] == 0){break;}
                            if(vect[cont][cont1] != ':' ){
                                //printf("    DATA: \'%c\'\n",vect[cont][cont1]);
                                concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                            }else{
                                break;
                            }
                        }//Despues concatena el atributo
                        contador++;contador++;cont1++;cont1++;
                    }else if(vect[cont][cont1+1] == ':'){
                        printf("                    \033[%dmErr: \033[%dmen parametro \"%c\" no debe tener ningun valor\033[0m\n" ,ROJO,MAGENTA,'P');
                        final[0] = compare[0] = '\0';
                        return;
                    }
                }else{
                    while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                        if(vect[cont][cont1] != ':'){
                            //printf("    DATA: \'%c\'\n",vect[cont][cont1]);
                            concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                        }else{
                            break;
                        }
                    }//Despues concatena el atributo
                    contador++;contador++;cont1++;cont1++;
                }
            }else if(get_size(vect[cont]) == cont1+1){
                if(vect[cont][cont1] == 'p' || vect[cont][cont1] == 'P'){
                    aux = 1;
                }
            }

            if(aux == 0){
                for(;cont1 < tama;cont1++){
                    concatenar_char(final,vect[cont][cont1]);
                }
                //printf("    FILL: %s,\'%s\'\n",compare,final);
            }else{
                concatenar_char(compare,vect[cont][cont1]);
                //printf("    ONLY: \'%s\'\n",compare);
            }
            if(strcasecmp(compare, ID)==0){
                //printf("ID: \'%s\'\n",final);
                int exceso = 0;
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            exceso++;
                            if(exceso <= 10){
                                concatenar_char(r_id,final[auxi]);
                            }else{
                                printf("                    \033[%dmErr: \033[%dmen parametro \"%s\" el tamaño excede de 10\033[0m\n" ,ROJO,MAGENTA,final);
                                final[0] = compare[0] = '\0';
                                return;
                            }
                        }else{
                            break;
                        }
                    }
                    o_id = 1;
                }else{
                    if(get_size(final) <= 10){
                        strcpy(r_id,final);
                        o_id = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmen parametro \"%s\" el tamaño excede de 10\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        return;
                    }

                }
            }else if(strcasecmp(compare, PATH)==0){
                //printf("PATH: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_path,final[auxi]);
                        }else{
                            break;
                        }
                    }
                    o_path = 1;
                }else{
                    strcpy(r_path,final);
                    o_path = 1;
                }
            }else if(strcasecmp(compare, SIZE)==0){
                //printf("SIZE: \'%s\'\n",final);
                r_size = atoi(final);
                if(r_size > 0){
                   n_size = 1;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" valor negativo.\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }else if(strcasecmp(compare, CCONT)==0 || strcasecmp(compare, CONTENT)==0){
                //printf("CONT: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_cont,final[auxi]);
                        }else{
                            break;
                        }
                    }
                    n_cont = 1;
                }else{
                    strcpy(r_cont,final);
                    n_cont = 1;
                }
            }else if(strcasecmp(compare, P)==0){
                //puts("P: crear carpeta padre");
                r_p = 1;
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verifica parámetros obligatorios para REMOVER */
        if(o_id == 1 && o_path == 1){
            //crear_reporte(r_path,a_name,r_ext,r_id,r_name);
            if(r_p == 1){
               //#    buscar_id_crear_archivos(r_id,r_path,1,r_size);
            }
            if(r_p == 0){
                 //#    buscar_id_crear_archivos(r_id,r_path,0,r_size);
            }
            printf("    SUCCESS EXEC:\'%s\', \'%s\', \'%d\',\'%d\', \'%s\'\n", r_id, r_path, r_p, r_size, r_cont);
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analiza el comando CAT para mostrar contenido de archivo */
    else if(strcasecmp(CAT,vect[0]) == 0){

        printf("  \033[%dmMOSTRAR CONTENIDO ARCHIVO: %s\033[0m\a\n",VERDE,vect[0]);
        char r_id[10], *r_path[200];
             r_id[0] = r_path[0] = '\0';
        //Para verificar si se ingresaron los parametros obligatorios
        int o_id = 0, o_path = 0, contact = 0;
        char* substr = malloc(sizeof(char)*5+1);
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }
            }//Despues concatena el atributo
            contador++;contador++;cont1++;cont1++;
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            /*for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }*/
            strncpy(substr, compare, 4);
            printf("SUB STRING: \'%s\'\n",substr);
            if(strcasecmp(compare, ID)==0){
                printf("ID: \'%s\'\n",final);
                int exceso = 0;
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            exceso++;
                            if(exceso <= 10){
                                concatenar_char(r_id,final[auxi]);
                            }else{
                                printf("                    \033[%dmErr: \033[%dmen parametro \"%s\" el tamaño excede de 10\033[0m\n" ,ROJO,MAGENTA,final);
                                final[0] = compare[0] = '\0';
                                return;
                            }
                        }else{
                            break;
                        }
                    }
                    o_id = 1;
                }else{
                    if(get_size(final) <= 10){
                        strcpy(r_id,final);
                        o_id = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmen parametro \"%s\" el tamaño excede de 10\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        return;
                    }
                }
            }else if(strcasecmp(substr, FFILE)==0){
                printf("FILE: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                r_path[contact] = malloc(sizeof(final)+1);
                substr[0] = '\0';int val = 0;
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_path[contact][val],final[auxi]);val++;
                        }else{
                            break;
                        }
                    }
                    o_path = 1;contact++;
                }else{

                    strcpy(r_path[contact],final);
                    contact++;
                    o_path = 1;
                }
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verifica parámetros obligatorios para REMOVER */
        if(o_id == 1 && o_path == 1){
            //crear_reporte(r_path,a_name,r_ext,r_id,r_name);
            for(cont=0; cont < contact; cont++){
                printf("    SUCCESS EXEC:\'%s\', \'%s\'\n", r_id, r_path[cont]);
            }

        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analiza el comando REM para eliminar archivo o carpeta */
    else if(strcasecmp(RM,vect[0]) == 0){
        printf("  \033[%dmELIMINAR ARCHIVO: %s\033[0m\a\n",VERDE,vect[0]);
        char r_id[10], r_path[200];
             r_id[0] = r_path[0] = '\0';
        //Para verificar si se ingresaron los parametros obligatorios
        int r_rf = 0, o_id = 0, o_path = 0;

        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0, aux = 0;
            //printf("Tam: %s - %d,%d\n",vect[cont],get_size(vect[cont]), cont1+1);
            if(get_size(vect[cont]) > cont1+2){
                if(vect[cont][cont1] == 'r' || vect[cont][cont1] == 'R'){
                    if(vect[cont][cont1+1] != 'a' || vect[cont][cont1+1] != 'A'){
                        while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                            if(vect[cont][cont1] == 0){break;}
                            if(vect[cont][cont1] != ':' ){
                                //printf("    DATA: \'%c\'\n",vect[cont][cont1]);
                                concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                            }else{
                                break;
                            }
                        }//Despues concatena el atributo
                        contador++;contador++;cont1++;cont1++;
                    }else if(vect[cont][cont1+1] == ':'){
                        printf("                    \033[%dmErr: \033[%dmen parametro \"%c\" no debe tener ningun valor\033[0m\n" ,ROJO,MAGENTA,'P');
                        final[0] = compare[0] = '\0';
                        return;
                    }
                }else{
                    while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                        if(vect[cont][cont1] != ':'){
                            //printf("    DATA: \'%c\'\n",vect[cont][cont1]);
                            concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                        }else{
                            break;
                        }
                    }//Despues concatena el atributo
                    contador++;contador++;cont1++;cont1++;
                }
            }else if(get_size(vect[cont]) == cont1+1){
                if(vect[cont][cont1] == 'r' || vect[cont][cont1] == 'R'){
                    aux = 1;
                }
            }

            if(aux == 0){
                for(;cont1 < tama;cont1++){
                    concatenar_char(final,vect[cont][cont1]);
                }
                //printf("    FILL: %s,\'%s\'\n",compare,final);
            }else{
                concatenar_char(compare,vect[cont][cont1]);
                //printf("    ONLY: \'%s\'\n",compare);
            }
            if(strcasecmp(compare, ID)==0){
                //printf("ID: \'%s\'\n",final);
                int exceso = 0;
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            exceso++;
                            if(exceso <= 10){
                                concatenar_char(r_id,final[auxi]);
                            }else{
                                printf("                    \033[%dmErr: \033[%dmen parametro \"%s\" el tamaño excede de 10\033[0m\n" ,ROJO,MAGENTA,final);
                                final[0] = compare[0] = '\0';
                                return;
                            }
                        }else{
                            break;
                        }
                    }
                    o_id = 1;
                }else{
                    if(get_size(final) <= 10){
                        strcpy(r_id,final);
                        o_id = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmen parametro \"%s\" el tamaño excede de 10\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        return;
                    }

                }
            }else if(strcasecmp(compare, PATH)==0){
                //printf("PATH: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_path,final[auxi]);
                        }else{
                            break;
                        }
                    }
                    o_path = 1;
                }else{
                    strcpy(r_path,final);
                    o_path = 1;
                }
            }else if(strcasecmp(final, RF)==0){
                //puts("RF: crear carpeta padre");
                r_rf = 1;
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verifica parámetros obligatorios para REMOVER */
        if(o_id == 1 && o_path == 1){
            //crear_reporte(r_path,a_name,r_ext,r_id,r_name);
            if(r_rf == 1){
               //#    buscar_id_crear_archivos(r_id,r_path,1,r_size);
            }
            if(r_rf == 0){
                 //#    buscar_id_crear_archivos(r_id,r_path,0,r_size);
            }
            printf("    SUCCESS EXEC:\'%s\', \'%s\', \'%d\'\n", r_id, r_path, r_rf);
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analiza el comando EDIT para editar archivo o carpeta */
    else if(strcasecmp(EDIT,vect[0]) == 0){
        printf("  \033[%dmEDITAR ARCHIVO: %s\033[0m\a\n",VERDE,vect[0]);

        char r_path[300], r_id[300], r_cont[300];
             r_path[0] =  r_id[0] =  r_cont[0] = '\0';
        int  o_path = 0,  o_id = 0,  o_cont = 0,  o_size = 0, r_size = 0;
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }
            }//Despues concatena el atributo
            contador++;contador++;cont1++;cont1++;
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            //printf("    DATA: %s,\'%s\'\n",compare,final);
            if(strcasecmp(compare, PATH)==0){
                //PATH: indicará el id que se generó con el comando mount de la primera fase
                printf("PATH: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_path,final[auxi]);
                        }else{
                            o_path = 1;
                            break;
                        }
                    }
                    o_path = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_path,final);
                        o_path = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, ID)==0){
                //ID: indicará el id que se generó con el comando mount de la primera fase
                printf("ID: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_id,final[auxi]);
                        }else{
                            o_id = 1;
                            break;
                        }
                    }
                    o_id = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_id,final);
                        o_id = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, SIZE)==0){
                printf("SIZE: \'%s\'\n",final);
                r_size = atoi(final);
                if(r_size > 0){
                    o_size= 1;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\", \'%s\' tipo incompatible!\033[0m\n" ,ROJO,MAGENTA,SIZE,final);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }else if(strcasecmp(compare, CCONT)==0){
                //CONT: indicará el id que se generó con el comando mount de la primera fase
                printf("CONT: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_cont,final[auxi]);
                        }else{
                            o_cont = 1;
                            break;
                        }
                    }
                    o_cont = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_cont,final);
                        o_cont = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verificar valores del variables no obligatorias
         * Si existen, si no se inicializa con valor por defecto */

        /* Verifica parámetros obligatorios para INICIAR SESION */
        if(o_path == 1 && o_id == 1 && (o_cont == 1 || o_size == 1)){
            printf("    EDITADO: [%s] %s, \'%s\', \'%d\'\n",r_path,r_id,r_cont,r_size);
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }
    /*
     * Analiza el comando REN para editar archivo o carpeta */
    else if(strcasecmp(REN,vect[0]) == 0){
        printf("  \033[%dmRENOMBRAR ARCHIVO: %s\033[0m\a\n",VERDE,vect[0]);

        char r_path[300], r_id[300], r_name[300];
             r_path[0] =  r_id[0] =  r_name[0] = '\0';
        int  o_path = 0,  o_id = 0,  o_name = 0;
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }
            }//Despues concatena el atributo
            contador++;contador++;cont1++;cont1++;
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            //printf("    DATA: %s,\'%s\'\n",compare,final);
            if(strcasecmp(compare, PATH)==0){
                //PATH: indicará el id que se generó con el comando mount de la primera fase
                //printf("PATH: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_path,final[auxi]);
                        }else{
                            o_path = 1;
                            break;
                        }
                    }
                    o_path = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_path,final);
                        o_path = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, ID)==0){
                //ID: indicará el id que se generó con el comando mount de la primera fase
                //printf("ID: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_id,final[auxi]);
                        }else{
                            o_id = 1;
                            break;
                        }
                    }
                    o_id = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_id,final);
                        o_id = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, NAME)==0){
                //NAME: indicará el id que se generó con el comando mount de la primera fase
                //printf("NAME: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_name,final[auxi]);
                        }else{
                            o_name = 1;
                            break;
                        }
                    }
                    o_name = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_name,final);
                        o_name = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verificar valores del variables no obligatorias
         * Si existen, si no se inicializa con valor por defecto */

        /* Verifica parámetros obligatorios para INICIAR SESION */
        if(o_path == 1 && o_id == 1 && o_name == 1){
            printf("    EDITADO: [%s] %s, \'%s\', \'%d\'\s",r_path,r_id,r_name);
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analiza el comando MKDIR para crear archivos */
    else if(strcasecmp(MKDIR,vect[0]) == 0){

        printf("  \033[%dmCREAR DIRECTORIO: %s\033[0m\a\n",VERDE,vect[0]);
        char r_id[10], r_path[200];
             r_id[0] = r_path[0] = '\0';
        //Para verificar si se ingresaron los parametros obligatorios
        int r_p = 0, o_id = 0, o_path = 0;

        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0, aux = 0;
            //printf("Tam: %s - %d,%d\n",vect[cont],get_size(vect[cont]), cont1+1);
            if(get_size(vect[cont]) > cont1+1){
                if(vect[cont][cont1] == 'p' || vect[cont][cont1] == 'P'){
                    if(vect[cont][cont1+1] != 'a' || vect[cont][cont1+1] != 'A'){
                        while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                            if(vect[cont][cont1] == 0){break;}
                            if(vect[cont][cont1] != ':' ){
                                //printf("    DATA: \'%c\'\n",vect[cont][cont1]);
                                concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                            }else{
                                break;
                            }
                        }//Despues concatena el atributo
                        contador++;contador++;cont1++;cont1++;
                    }else if(vect[cont][cont1+1] == ':'){
                        printf("                    \033[%dmErr: \033[%dmen parametro \"%c\" no debe tener ningun valor\033[0m\n" ,ROJO,MAGENTA,'P');
                        final[0] = compare[0] = '\0';
                        return;
                    }
                }else{
                    while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                        if(vect[cont][cont1] != ':'){
                            //printf("    DATA: \'%c\'\n",vect[cont][cont1]);
                            concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                        }else{
                            break;
                        }
                    }//Despues concatena el atributo
                    contador++;contador++;cont1++;cont1++;
                }
            }else if(get_size(vect[cont]) == cont1+1){
                if(vect[cont][cont1] == 'p' || vect[cont][cont1] == 'P'){
                    aux = 1;
                }
            }

            if(aux == 0){
                for(;cont1 < tama;cont1++){
                    concatenar_char(final,vect[cont][cont1]);
                }
                //printf("    FILL: %s,\'%s\'\n",compare,final);
            }else{
                concatenar_char(compare,vect[cont][cont1]);
                //printf("    ONLY: \'%s\'\n",compare);
            }
            if(strcasecmp(compare, ID)==0){
                //printf("ID: \'%s\'\n",final);
                int exceso = 0;
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            exceso++;
                            if(exceso <= 10){
                                concatenar_char(r_id,final[auxi]);
                            }else{
                                printf("                    \033[%dmErr: \033[%dmen parametro \"%s\" el tamaño excede de 10\033[0m\n" ,ROJO,MAGENTA,final);
                                final[0] = compare[0] = '\0';
                                return;
                            }
                        }else{
                            break;
                        }
                    }
                    o_id = 1;
                }else{
                    if(get_size(final) <= 10){
                        strcpy(r_id,final);
                        o_id = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmen parametro \"%s\" el tamaño excede de 10\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        return;
                    }

                }
            }else if(strcasecmp(compare, PATH)==0){
                //printf("PATH: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_path,final[auxi]);
                        }else{
                            break;
                        }
                    }
                    o_path = 1;
                }else{
                    strcpy(r_path,final);
                    o_path = 1;
                }
            }else if(strcasecmp(compare, P)==0){
                //puts("P: crear carpeta padre");
                r_p = 1;
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verifica parámetros obligatorios para REMOVER */
        if(o_id == 1 && o_path == 1){
            //crear_reporte(r_path,a_name,r_ext,r_id,r_name);
            if(r_p == 1){
               //#    buscar_id_crear_archivos(r_id,r_path,1,r_size);
            }
            if(r_p == 0){
                 //#    buscar_id_crear_archivos(r_id,r_path,0,r_size);
            }
            printf("    SUCCESS EXEC:\'%s\', \'%s\', \'%d\'\n", r_id, r_path, r_p);
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analiza el comando CP para editar archivo o carpeta */
    else if(strcasecmp(CP,vect[0]) == 0){
        printf("  \033[%dmRENOMBRAR ARCHIVO: %s\033[0m\a\n",VERDE,vect[0]);

        char r_path[300], r_id[300], r_dest[300], r_iddest[300];
             r_path[0] =  r_id[0] =  r_dest[0] =  r_iddest[0] ='\0';
        int  o_path = 0,  o_id = 0,  o_dest = 0, o_iddest = 0;
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }
            }//Despues concatena el atributo
            contador++;contador++;cont1++;cont1++;
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            //printf("    DATA: %s,\'%s\'\n",compare,final);
            if(strcasecmp(compare, PATH)==0){
                //PATH: indicará el id que se generó con el comando mount de la primera fase
                //printf("PATH: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_path,final[auxi]);
                        }else{
                            o_path = 1;
                            break;
                        }
                    }
                    o_path = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_path,final);
                        o_path = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, ID)==0){
                //ID: indicará el id que se generó con el comando mount de la primera fase
                //printf("ID: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_id,final[auxi]);
                        }else{
                            o_id = 1;
                            break;
                        }
                    }
                    o_id = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_id,final);
                        o_id = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, IDDEST)==0){
                //IDDEST: indicará el id que se generó con el comando mount de la primera fase
                //printf("IDDEST: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_iddest,final[auxi]);
                        }else{
                            o_iddest = 1;
                            break;
                        }
                    }
                    o_iddest = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_iddest,final);
                        o_iddest = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, DEST)==0){
                //DEST: indicará el id que se generó con el comando mount de la primera fase
                //printf("DEST: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_dest,final[auxi]);
                        }else{
                            o_dest = 1;
                            break;
                        }
                    }
                    o_dest = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_dest,final);
                        o_dest = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verificar valores del variables no obligatorias
         * Si existen, si no se inicializa con valor por defecto */

        /* Verifica parámetros obligatorios para INICIAR SESION */
        if(o_path == 1 && o_id == 1 && o_dest == 1 && o_iddest == 1){
            printf("    EDITADO: [%s] %s, \'%s\', \'%s\'\n",r_path,r_id,r_dest,r_iddest);
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }

    /*
     * Analiza el comando CP para editar archivo o carpeta */
    else if(strcasecmp(MV,vect[0]) == 0){
        printf("  \033[%dmRENOMBRAR ARCHIVO: %s\033[0m\a\n",VERDE,vect[0]);

        char r_path[300], r_id[300], r_dest[300], r_iddest[300];
             r_path[0] =  r_id[0] =  r_dest[0] =  r_iddest[0] ='\0';
        int  o_path = 0,  o_id = 0,  o_dest = 0, o_iddest = 0;
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }
            }//Despues concatena el atributo
            contador++;contador++;cont1++;cont1++;
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            //printf("    DATA: %s,\'%s\'\n",compare,final);
            if(strcasecmp(compare, PATH)==0){
                //PATH: indicará el id que se generó con el comando mount de la primera fase
                //printf("PATH: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_path,final[auxi]);
                        }else{
                            o_path = 1;
                            break;
                        }
                    }
                    o_path = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_path,final);
                        o_path = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, ID)==0){
                //ID: indicará el id que se generó con el comando mount de la primera fase
                //printf("ID: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_id,final[auxi]);
                        }else{
                            o_id = 1;
                            break;
                        }
                    }
                    o_id = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_id,final);
                        o_id = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, IDDEST)==0){
                //IDDEST: indicará el id que se generó con el comando mount de la primera fase
                //printf("IDDEST: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_iddest,final[auxi]);
                        }else{
                            o_iddest = 1;
                            break;
                        }
                    }
                    o_iddest = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_iddest,final);
                        o_iddest = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, DEST)==0){
                //DEST: indicará el id que se generó con el comando mount de la primera fase
                //printf("DEST: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_dest,final[auxi]);
                        }else{
                            o_dest = 1;
                            break;
                        }
                    }
                    o_dest = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_dest,final);
                        o_dest = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verificar valores del variables no obligatorias
         * Si existen, si no se inicializa con valor por defecto */

        /* Verifica parámetros obligatorios para INICIAR SESION */
        if(o_path == 1 && o_id == 1 && o_dest == 1 && o_iddest == 1){
            printf("    MOVIDO: [%s] %s, \'%s\', \'%s\'\n",r_path,r_id,r_dest,r_iddest);
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }


    //FIND

    //CHOWN

    /*
     * Analizador de la CHGRP  */
    else if(strcasecmp(CHGRP,vect[0]) == 0){
        printf("  \033[%dmCREAR USUARIO: %s\033[0m\a\n",VERDE,vect[0]);

        char r_usr[300], r_grp[300];
             r_usr[0] =  r_grp[0] = '\0';
        int  o_usr = 0,  o_grp = 0;
        for(cont = 1;cont < esta;cont++){
            char compare[200], final[400];compare[0] = final[0] = '\0';
            int tama = get_size(vect[cont]), contador = 0;
            while(1){//Concatena todo lo que viene entre '-' y '='; ej: - 'size' =
                if(vect[cont][cont1] == 0){break;}
                if(vect[cont][cont1] != ':'){
                    concatenar_char(compare,vect[cont][cont1]);cont1++;contador++;
                }else{
                    break;
                }

            }//Despues concatena el atributo
            contador++;contador++;cont1++;cont1++;
            for(;cont1 < tama;cont1++){
                concatenar_char(final,vect[cont][cont1]);
            }
            //printf("    DATA: %s,\'%s\'\n",compare,final);
            if(strcasecmp(compare, USR)==0){
                //USR: indicará el id que se generó con el comando mount de la primera fase
                printf("USR: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_usr,final[auxi]);
                        }else{
                            o_usr = 1;
                            break;
                        }
                    }
                    o_usr = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_usr,final);
                        o_usr = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else if(strcasecmp(compare, GRP)==0){
                //GRP: indicará el id que se generó con el comando mount de la primera fase
                printf("GRP: \'%s\'\n",final);
                /* Verificar si no esta entre comillas */
                if(final[0] == '\"'){int auxi = 1, end = sizeof(final);
                    for(;auxi < end;auxi++){
                        if(final[auxi] != '"'){
                            concatenar_char(r_grp,final[auxi]);
                        }else{
                            o_grp = 1;
                            break;
                        }
                    }
                    o_grp = 1;
                }else{
                    if(strcmp(final,"") != 0){
                        strcpy(r_grp,final);
                        o_grp = 1;
                    }else{
                        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,final);
                        final[0] = compare[0] = '\0';
                        tama = 0;cont1 = 1; //Reinicializar parámetros
                        return;
                    }
                }
            }else{
                //puts("Entra y truena");
                if(compare[0] == 0){
                    //Ignorara
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    //return;
                }else{
                    printf("                    \033[%dmErr: \033[%dmcommand \"%s\" incompatible!\033[0m\n" ,ROJO,MAGENTA,compare);
                    final[0] = compare[0] = '\0';
                    tama = 0;cont1 = 1; //Reinicializar parámetros
                    return;
                }
            }
            final[0] = compare[0] = '\0';
            tama = 0;cont1 = 1; //Reinicializar parámetros
            //printf("    PARAMETROS: %s\n",vect[cont]);
        }
        /* Verificar valores del variables no obligatorias
         * Si existen, si no se inicializa con valor por defecto */

        /* Verifica parámetros obligatorios para INICIAR SESION */
        if(o_usr == 1 && o_grp == 1){
            if(get_size(r_usr) < 10 && get_size(r_grp) < 10){
                //crear_reporte(r_path,a_name,r_ext,r_id,r_name);
                printf("    GRUPO CAMBIDADO: [%s] %s\n",r_usr,r_grp);
            }else{
                printf("                    \033[%dmErr: \033[%dmen los parametros, exceden el tamaño \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
                return;
            }
        }else{
            printf("                    \033[%dmErr: \033[%dmfaltan parametros en \"%s\" \033[0m\n" ,ROJO,MAGENTA,vect[0]);
            return;
        }
    }



    //LN


    /* End of all (analyzer) */
    else{
        printf("                    \033[%dmErr: \033[%dmcommand \"%s\" not found!\033[0m\a\a\n" ,ROJO,MAGENTA,vect[0]);
    }

    printf("                        FINALIZANDO PROCESO... %s \n",vect[0]);
}







/*
 * Analizar compando */
void analizar_comando(char *cmd){
    int cont = 0, tamanio = get_size(cmd), esta = 0, param = 0;
    char temp[600];temp[0] = '\0';
    char *vect[100];
    for(;cont <= tamanio;cont++){
        if(cmd[cont] != NULL){
            if(param == 0){
                /* Si encuentra un " se queda en ese estado hasta que encuentra el otro " */
                if(cmd[cont] == '"')param = 1;//puts("Encontro una comilla");
                if(cmd[cont] != ' '){
                    concatenar_char(temp,cmd[cont]);
                    //printf("Char: %c\n",cmd[cont]);
                }else{
                    if( get_size(temp) != 0){
                        //printf("Vaci: \'%d\'\n",get_size(temp));
                        vect[esta] = malloc(sizeof(temp)+1);
                        strcpy(vect[esta], temp);
                        esta++;
                        temp[0] = '\0';
                        //printf("    Word: %s\n",temp);
                    }
                }
            }else{
                if(cmd[cont] == '"')param = 0;//puts("Encontro una comilla");
                concatenar_char(temp,cmd[cont]);
            }

        }else{
            //printf("    Word: %s\n",temp);
            vect[esta]  = malloc(sizeof(temp)+1);
            strcpy(vect[esta], temp);
            esta++;
        }
    }

    /* Mostrar los parametros encontradso
       Tieme un error: cuando solo viene
       un caracter sin más, usa el caracter */
    for(cont = 0;cont < esta;cont++){
        printf("    PARAMETROS: %s\n",vect[cont]);
    }
}







//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    AREA DE MENSAJES DE ESTADO
/*
 * Funciones auxiliares para el analisis de las entradas
 * descompone y analizan los comandos de consola/prompt */

void quitar_espacio(char s[], char c){
    unsigned int i, j;
    for(i = j = 0; s[i] != '\0'; i++)
        if(s[i] != c)
        s[j++] = s[i];
    s[j] = '\0';
}

void quitar_espacios_en_blanco(char s[], char c){
    unsigned int i, j;
    for(i = j = 0; s[i] != '\0'; i++)
       if(s[i] != ' '){
            s[j++] = s[i];
            //printf("CHAR: %c\n",s[i]);
       }else{
            s[j++] = '_';
            //printf("CHAR: %c\n",s[i]);
       }
    s[j] = '\0';
}

int comparar(char *a,char *b){

    int aa = strlen(a);
    int bb = strlen(b);
    if(a != b){
        quitar_espacio(a,' ');
        quitar_espacio(b,' ');

        aa = strlen(a);
        bb = strlen(b);
    }
    if(aa != bb){
        //printf("Longitud %s,%s (%d,%d)\n",a,b,strlen(a),strlen(b));
        return -1;
    }else{int cc;
        for(cc = 0; cc < aa; cc++){
            if(a[cc] != b[cc]){
                //printf("Difieren en: %c,%c\n", a[cc],b[cc]);
                return 1;
            }
        }
    }
    return 0;
}

int comparar_add(char *a,char *b){

    quitar_espacio(a,' ');

    int aa = strlen(a);
    int bb = strlen(b);

    if(aa != bb){
        int cc;
        for(cc = 0; cc < bb; cc++){
            if(a[cc] != b[cc]){
                //printf("Difieren en: %c,%c\n", a[cc],b[cc]);
                return 0;
            }
        }
    }
    return 1;
}

void concatenar_char(char* s, char c){
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}

/*
 * Crear carpeta o directorio en el sistema */
void crear_carpeta(char *carpeta){
    if((directorio = opendir(&carpeta)) == NULL ){
        /* Verificar directroio, si no existe lo crea
           si no existe mostrar mensaje de error      */
        exe("creando carpeta... ",carpeta);
        //char *carpeta="/home/prueba/disco 1/";
        char *array[30];
        char *ptop, *pend;
        char *wk = malloc(sizeof(char)*(strlen(carpeta)+3));//wk[1024];
        int i,kk = 1, size = sizeof(array)/sizeof(char*);
            strcpy(wk, carpeta);
            strcat(wk, "/");
            for(i=0, ptop=wk;i<size;++i){
                if(NULL!=(pend=strstr(ptop, "/"))){
                    *pend='\0';
                    array[i]=strdup(ptop);
                    ptop=pend+1;

                } else {
                     kk++;
                    array[i]=NULL;
                    //break;
                }
            }
            //printf("TAM: %d\n",kk);
            for(i = 1;i<size-kk;++i)
                if(array[i] != NULL){
                    if(i==1){
                        char tt[400];
                        strcpy(tt,"/");
                        strcat(tt,array[i]);
                        strcat(tt,"/");
                        array[i][0] = '\0';
                        strcpy(array[i],tt);
                        //printf("array: %s\n", tt);
                        //printf("array: %s\n", array[i]);
                    }else{
                        strcat(array[1],array[i]);
                        strcat(array[1],"/");
                    }
                    if(mkdir(array[1], 0777) == -1){
                        war("no se puede crear carpeta, se denego permiso o ya existe: ", array[1]);
                    }else{
                        //printf("array[%d]=\"%s\"\n", i, array[1]);
                        //closedir(array[1]);
                    }
                }else{
                    break;
                }

    }else{
        war("drectorio existente",carpeta);
    }
}

/*
 * Verifica carpeta o directorio en el sistema */
int verificar_carpeta(char *carpeta){
    if((directorio = opendir(carpeta)) == NULL ){
        return -1;
    }else{
        return 0;
    }
}

/*
 * Verifica archivo en el sistema
void set_time(time_t t){
    //time_t t = time(0);
    struct tm *tcreacion = localtime(&t);
    strftime(fecha,16,"%d/%m/%y %H:%M",tcreacion);
}*/

/*
 * Verifica archivo en el sistema */
time_t get_time(){
    time_t t = time(0);
    //struct tm *tlocal = localtime(&t);
    //strftime(fecha,16,"%d/%m/%y %H:%M",tlocal);
    return t;
}

/*
 * Establecer archivo con directorio y extensión */
void establecer_nombre(char *path,char *nombre){
    //ubicacion_archivo[0] = '\0';
    /* make space for the new string (should check the return value ...) */
    ubicacion_archivo = malloc(get_size(path)+get_size(nombre)+4);
    strcpy(ubicacion_archivo, path);   /* copy name into the new var */
    strcat(ubicacion_archivo, nombre); /* add the name */
    strcat(ubicacion_archivo, ".dsk"); /* add the extension */

}
/*
 * Establecer archivo con directorio y extensión */
void establecer_nombre_dot(char *path,char *nombre){
    //ubicacion_archivo[0] = '\0';
    /* make space for the new string (should check the return value ...) */
    ubicacion_archivo = malloc(get_size(path)+get_size(nombre)+4);
    strcpy(ubicacion_archivo, path);   /* copy name into the new var */
    strcat(ubicacion_archivo, nombre); /* add the name */
    //strcat(ubicacion_archivo, ".dsk"); /* add the extension */

}

int get_size(char *informacion){
    int i=0;
    while((informacion[i]!=0) && (informacion[i]!=127))
        i++;
    return i;
}

int existe_archivo(char* file){
    FILE* f = NULL;
    f = fopen(file,"rb");
    if(f == NULL && errno == ENOENT){
        return 0;
    }else {
        fclose(f);
        return 1;
    }
}

void limpiar_cadena(char *cadena)
{
  char *p;
  p = strchr (cadena, '\n');
  if (p)
    *p = '\0';
}

void suc(char *info, char *why){
    printf("                    \033[%dmInfo: \033[%dm \"%s\" %s \033[0m\n" ,AMARILLO,MAGENTA,info, why);
}

void war(char *error, char *why){
    printf("                    \033[%dmWarn: \033[%dm \"%s\" en.. %s \033[0m\n" ,AMARILLO,MAGENTA,error, why);
}

void err(char *error, char *why){
    printf("                    \033[%dmErr: \033[%dm \"%s\" por.. %s \033[0m\n" ,ROJO,MAGENTA,error, why);
}

void exe(char *what, char *where){
    printf("    \033[%dm%s %s\033[0m\a\n",VERDE,what,where);
}

void inf(char *what){
    printf("    \033[%dmInfo: %s \033[0m\a\n",CYAN,what);
}

char *get_name(char *disco){
    int  e = 0;
    //printf ("Cadena: %s\n",disco);
    char *nueva_cadena;char *r_name;
    char *temporal;
    char *nombre_disco[20];
    char cadena[200];strcpy(cadena, disco);
    nueva_cadena = strtok (cadena,"");
    //char *cadenaa ="\"/home/lex/data/mis discos/Disco3.dsk\"";
    nueva_cadena = strtok (cadena,"\"");
    while (nueva_cadena != NULL)
    {
        //printf ("   Con split: %s\n",nueva_cadena);
        if(1){
            temporal = strtok(nueva_cadena, "/");
            if(temporal){
                // Verifica el primer dato o split/word
                //printf("        1) %s\n", temporal);
                nombre_disco[e] = temporal;
            }

            while(temporal){
                e++;
                temporal = strtok(NULL, "/");
                if(temporal){
                    //printf("        %d) %s\n",e, temporal);
                    nombre_disco[e] = temporal;
                }else{
                    break;
                }
            }
            int a = 0;
            if(1){
                char *temp = strtok(nombre_disco[e-1], ".");
                if(temp){
                    strcpy(r_name, temp);                       //Guardar NOMBRE
                    printf("    Nombre: %s\n", r_name);
                }a++;temporal = strtok(NULL, ".");
            }

        }
        nueva_cadena = strtok (NULL, "\"");
    }
    return r_name;

}

char *get_path(char *disco){
    int  e = 0;
    //printf ("Cadena: %s\n",disco);
    char *nueva_cadena;
    char *temporal;
    char *nombre_disco[20];
    char cadena[400];strcpy(cadena, disco);
    nueva_cadena = strtok (cadena,"");
    //char *cadenaa ="\"/home/lex/data/mis discos/Disco3.dsk\"";
    nueva_cadena = strtok (cadena,"");
    while (nueva_cadena != NULL)
    {
        //printf ("   Con split: %s\n",nueva_cadena);
        if(1){
            temporal = strtok(nueva_cadena, "/");
            if(temporal){
                // Verifica el primer dato o split/word
                //printf("        0) %s\n", temporal);
                nombre_disco[e] = malloc(sizeof(temporal));
                strcpy(nombre_disco[e],temporal);
            }

            while(temporal){
                e++;
                temporal = strtok(NULL, "/");
                if(temporal){
                    //printf("        %d) %s\n",e, temporal);
                    nombre_disco[e] = malloc(sizeof(temporal));
                    strcpy(nombre_disco[e],temporal);
                }else{
                    break;
                }

            }
        }
        nueva_cadena = strtok (NULL, "\"");
    }
    char directorio[400];directorio[0]='\0';int da;
    strcpy(directorio, "/");
    strcat(directorio, nombre_disco[0]);
    strcat(directorio, "/");
    for(da = 1; da <e-1; da++ ){
        strcat(directorio,nombre_disco[da]);
        strcat(directorio, "/");
    }
    //printf("El final: %s\n", directorio);
    return directorio;

}

char *get_ext(char *disco){
    int  e = 0;
    char *nueva_cadena;char *r_name;
    char *temporal;
    char *nombre_disco[20];
    char cadena[200];strcpy(cadena, disco);
    nueva_cadena = strtok (cadena,"");
    //char *cadenaa ="\"/home/lex/data/mis discos/Disco3.dsk\"";
    nueva_cadena = strtok (cadena,"\"");
    while (nueva_cadena != NULL)
    {
        //printf ("   Con split: %s\n",nueva_cadena);
        if(1){
            temporal = strtok(nueva_cadena, "/");
            if(temporal){
                // Verifica el primer dato o split/word
                //printf("        1) %s\n", temporal);
                nombre_disco[e] = temporal;
            }

            while(temporal){
                e++;
                temporal = strtok(NULL, "/");
                if(temporal){
                    //printf("        %d) %s\n",e, temporal);
                    nombre_disco[e] = temporal;
                }else{
                    break;
                }
            }
            int a = 0;
            if(1){
                char *temp = strtok(nombre_disco[e-1], ".");
                if(temp){
                    strcpy(r_name, temp);                       //Guardar NOMBRE
                    //printf("    Nombre: %s\n", r_name);
                }a++;temporal = strtok(NULL, ".");
            }

        }
        nueva_cadena = strtok (NULL, "\"");
    }

    return r_name;

}
