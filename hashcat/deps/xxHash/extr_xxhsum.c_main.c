#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  endianess ;
typedef  int /*<<< orphan*/  algoType ;
typedef  int U32 ;

/* Variables and functions */
 int BMK_benchFiles (char const**,int,int) ; 
 int BMK_benchInternal (size_t,int) ; 
 int BMK_hashFiles (char const**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BMK_sanityCheck () ; 
 int /*<<< orphan*/  DISPLAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CONSOLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WELCOME_MESSAGE (char const* const) ; 
 size_t XXH_DEFAULT_SAMPLE_SIZE ; 
 int /*<<< orphan*/  algo_xxh32 ; 
 int badusage (char const* const) ; 
 int /*<<< orphan*/  big_endian ; 
 int checkFiles (char const**,int,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  g_defaultAlgo ; 
 int /*<<< orphan*/  g_displayLevel ; 
 void* g_nbIterations ; 
 int /*<<< orphan*/  little_endian ; 
 void* readU32FromChar (char const**) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * strstr (char const* const,char*) ; 
 int usage_advanced (char const* const) ; 

int main(int argc, const char** argv)
{
    int i, filenamesStart = 0;
    const char* const exename = argv[0];
    U32 benchmarkMode = 0;
    U32 fileCheckMode = 0;
    U32 strictMode    = 0;
    U32 statusOnly    = 0;
    U32 warn          = 0;
    U32 quiet         = 0;
    U32 specificTest  = 0;
    size_t keySize    = XXH_DEFAULT_SAMPLE_SIZE;
    algoType algo     = g_defaultAlgo;
    endianess displayEndianess = big_endian;

    /* special case : xxh32sum default to 32 bits checksum */
    if (strstr(exename, "xxh32sum") != NULL) algo = algo_xxh32;

    for(i=1; i<argc; i++) {
        const char* argument = argv[i];

        if(!argument) continue;   /* Protection, if argument empty */

        if (!strcmp(argument, "--little-endian")) { displayEndianess = little_endian; continue; }
        if (!strcmp(argument, "--check")) { fileCheckMode = 1; continue; }
        if (!strcmp(argument, "--strict")) { strictMode = 1; continue; }
        if (!strcmp(argument, "--status")) { statusOnly = 1; continue; }
        if (!strcmp(argument, "--quiet")) { quiet = 1; continue; }
        if (!strcmp(argument, "--warn")) { warn = 1; continue; }
        if (!strcmp(argument, "--help")) { return usage_advanced(exename); }
        if (!strcmp(argument, "--version")) { DISPLAY(WELCOME_MESSAGE(exename)); return 0; }

        if (*argument!='-') {
            if (filenamesStart==0) filenamesStart=i;   /* only supports a continuous list of filenames */
            continue;
        }

        /* command selection */
        argument++;   /* note : *argument=='-' */

        while (*argument!=0) {
            switch(*argument)
            {
            /* Display version */
            case 'V':
                DISPLAY(WELCOME_MESSAGE(exename)); return 0;

            /* Display help on usage */
            case 'h':
                return usage_advanced(exename);

            /* select hash algorithm */
            case 'H':
                algo = (algoType)(argument[1] - '0');
                argument+=2;
                break;

            /* File check mode */
            case 'c':
                fileCheckMode=1;
                argument++;
                break;

            /* Warning mode (file check mode only, alias of "--warning") */
            case 'w':
                warn=1;
                argument++;
                break;

            /* Trigger benchmark mode */
            case 'b':
                argument++;
                benchmarkMode = 1;
                specificTest = readU32FromChar(&argument);   /* select one specific test (hidden option) */
                break;

            /* Modify Nb Iterations (benchmark only) */
            case 'i':
                argument++;
                g_nbIterations = readU32FromChar(&argument);
                break;

            /* Modify Block size (benchmark only) */
            case 'B':
                argument++;
                keySize = readU32FromChar(&argument);
                break;

            /* Modify verbosity of benchmark output (hidden option) */
            case 'q':
                argument++;
                g_displayLevel--;
                break;

            default:
                return badusage(exename);
            }
        }
    }   /* for(i=1; i<argc; i++) */

    /* Check benchmark mode */
    if (benchmarkMode) {
        DISPLAYLEVEL(2, WELCOME_MESSAGE(exename) );
        BMK_sanityCheck();
        if (filenamesStart==0) return BMK_benchInternal(keySize, specificTest);
        return BMK_benchFiles(argv+filenamesStart, argc-filenamesStart, specificTest);
    }

    /* Check if input is defined as console; trigger an error in this case */
    if ( (filenamesStart==0) && IS_CONSOLE(stdin) ) return badusage(exename);

    if (filenamesStart==0) filenamesStart = argc;
    if (fileCheckMode) {
        return checkFiles(argv+filenamesStart, argc-filenamesStart,
                          displayEndianess, strictMode, statusOnly, warn, quiet);
    } else {
        return BMK_hashFiles(argv+filenamesStart, argc-filenamesStart, algo, displayEndianess);
    }
}