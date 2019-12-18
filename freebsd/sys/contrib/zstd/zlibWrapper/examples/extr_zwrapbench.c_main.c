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
typedef  void* U32 ;

/* Variables and functions */
 int /*<<< orphan*/  BMK_SetBlockSize (size_t) ; 
 int /*<<< orphan*/  BMK_SetNbIterations (void* const) ; 
 int /*<<< orphan*/  BMK_benchFiles (char const**,unsigned int,char const*,int,int) ; 
 int /*<<< orphan*/  BMK_setAdditionalParam (void*) ; 
 int /*<<< orphan*/  BMK_setNotificationLevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAN_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 char** UTIL_createFileList (char const**,unsigned int,char**,unsigned int*,int) ; 
 int /*<<< orphan*/  UTIL_freeFileList (char const**,char*) ; 
 int /*<<< orphan*/  WELCOME_MESSAGE ; 
 int ZSTDCLI_CLEVEL_DEFAULT ; 
 int /*<<< orphan*/  badusage (char const*) ; 
 int /*<<< orphan*/  displayOut ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  g_displayLevel ; 
 scalar_t__ malloc (int) ; 
 void* readU32FromChar (char const**) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 char toupper (char const) ; 
 int /*<<< orphan*/  usage (char const*) ; 
 int /*<<< orphan*/  waitEnter () ; 

int main(int argCount, char** argv)
{
    int argNb,
        main_pause=0,
        nextEntryIsDictionary=0,
        operationResult=0,
        nextArgumentIsFile=0;
    int cLevel = ZSTDCLI_CLEVEL_DEFAULT;
    int cLevelLast = 1;
    unsigned recursive = 0;
    const char** filenameTable = (const char**)malloc(argCount * sizeof(const char*));   /* argCount >= 1 */
    unsigned filenameIdx = 0;
    const char* programName = argv[0];
    const char* dictFileName = NULL;
    char* dynNameSpace = NULL;
#ifdef UTIL_HAS_CREATEFILELIST
    const char** fileNamesTable = NULL;
    char* fileNamesBuf = NULL;
    unsigned fileNamesNb;
#endif

    /* init */
    if (filenameTable==NULL) { DISPLAY("zstd: %s \n", strerror(errno)); exit(1); }
    displayOut = stderr;

    /* Pick out program name from path. Don't rely on stdlib because of conflicting behavior */
    {   size_t pos;
        for (pos = (int)strlen(programName); pos > 0; pos--) { if (programName[pos] == '/') { pos++; break; } }
        programName += pos;
    }

     /* command switches */
    for(argNb=1; argNb<argCount; argNb++) {
        const char* argument = argv[argNb];
        if(!argument) continue;   /* Protection if argument empty */

        if (nextArgumentIsFile==0) {

            /* long commands (--long-word) */
            if (!strcmp(argument, "--")) { nextArgumentIsFile=1; continue; }
            if (!strcmp(argument, "--version")) { displayOut=stdout; DISPLAY(WELCOME_MESSAGE); CLEAN_RETURN(0); }
            if (!strcmp(argument, "--help")) { displayOut=stdout; CLEAN_RETURN(usage(programName)); }
            if (!strcmp(argument, "--verbose")) { g_displayLevel++; continue; }
            if (!strcmp(argument, "--quiet")) { g_displayLevel--; continue; }

            /* Decode commands (note : aggregated commands are allowed) */
            if (argument[0]=='-') {
                argument++;

                while (argument[0]!=0) {
                    switch(argument[0])
                    {
                        /* Display help */
                    case 'V': displayOut=stdout; DISPLAY(WELCOME_MESSAGE); CLEAN_RETURN(0);   /* Version Only */
                    case 'H':
                    case 'h': displayOut=stdout; CLEAN_RETURN(usage(programName));

                        /* Use file content as dictionary */
                    case 'D': nextEntryIsDictionary = 1; argument++; break;

                        /* Verbose mode */
                    case 'v': g_displayLevel++; argument++; break;

                        /* Quiet mode */
                    case 'q': g_displayLevel--; argument++; break;

#ifdef UTIL_HAS_CREATEFILELIST
                        /* recursive */
                    case 'r': recursive=1; argument++; break;
#endif

                        /* Benchmark */
                    case 'b':
                            /* first compression Level */
                            argument++;
                            cLevel = readU32FromChar(&argument);
                            break;

                        /* range bench (benchmark only) */
                    case 'e':
                            /* last compression Level */
                            argument++;
                            cLevelLast = readU32FromChar(&argument);
                            break;

                        /* Modify Nb Iterations (benchmark only) */
                    case 'i':
                        argument++;
                        {   U32 const iters = readU32FromChar(&argument);
                            BMK_setNotificationLevel(g_displayLevel);
                            BMK_SetNbIterations(iters);
                        }
                        break;

                        /* cut input into blocks (benchmark only) */
                    case 'B':
                        argument++;
                        {   size_t bSize = readU32FromChar(&argument);
                            if (toupper(*argument)=='K') bSize<<=10, argument++;  /* allows using KB notation */
                            if (toupper(*argument)=='M') bSize<<=20, argument++;
                            if (toupper(*argument)=='B') argument++;
                            BMK_setNotificationLevel(g_displayLevel);
                            BMK_SetBlockSize(bSize);
                        }
                        break;

                        /* Pause at the end (-p) or set an additional param (-p#) (hidden option) */
                    case 'p': argument++;
                        if ((*argument>='0') && (*argument<='9')) {
                            BMK_setAdditionalParam(readU32FromChar(&argument));
                        } else
                            main_pause=1;
                        break;
                        /* unknown command */
                    default : CLEAN_RETURN(badusage(programName));
                    }
                }
                continue;
            }   /* if (argument[0]=='-') */

        }   /* if (nextArgumentIsAFile==0) */

        if (nextEntryIsDictionary) {
            nextEntryIsDictionary = 0;
            dictFileName = argument;
            continue;
        }

        /* add filename to list */
        filenameTable[filenameIdx++] = argument;
    }

    /* Welcome message (if verbose) */
    DISPLAYLEVEL(3, WELCOME_MESSAGE);

#ifdef UTIL_HAS_CREATEFILELIST
    if (recursive) {
        fileNamesTable = UTIL_createFileList(filenameTable, filenameIdx, &fileNamesBuf, &fileNamesNb, 1);
        if (fileNamesTable) {
            unsigned u;
            for (u=0; u<fileNamesNb; u++) DISPLAYLEVEL(4, "%u %s\n", u, fileNamesTable[u]);
            free((void*)filenameTable);
            filenameTable = fileNamesTable;
            filenameIdx = fileNamesNb;
        }
    }
#endif

    BMK_setNotificationLevel(g_displayLevel);
    BMK_benchFiles(filenameTable, filenameIdx, dictFileName, cLevel, cLevelLast);

_end:
    if (main_pause) waitEnter();
    free(dynNameSpace);
#ifdef UTIL_HAS_CREATEFILELIST
    if (fileNamesTable)
        UTIL_freeFileList(fileNamesTable, fileNamesBuf);
    else
#endif
        free((void*)filenameTable);
    return operationResult;
}