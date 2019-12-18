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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 int FUZ_compressibility_default ; 
 int FUZ_mallocTests (int,double,int) ; 
 int FUZ_usage (char const* const) ; 
 int /*<<< orphan*/  MAX (int,int /*<<< orphan*/ ) ; 
 int XXH32 (int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  ZSTD_VERSION_STRING ; 
 int basicUnitTests (int /*<<< orphan*/ ,double) ; 
 int fuzzerTests (int,int,int,int,double,int) ; 
 int /*<<< orphan*/  g_displayLevel ; 
 int getchar () ; 
 scalar_t__ longCommandWArg (char const**,char*) ; 
 int nbTestsDefault ; 
 int readU32FromChar (char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int main(int argc, const char** argv)
{
    U32 seed = 0;
    int seedset = 0;
    int argNb;
    int nbTests = nbTestsDefault;
    int testNb = 0;
    int proba = FUZ_compressibility_default;
    int result = 0;
    U32 mainPause = 0;
    U32 maxDuration = 0;
    int bigTests = 1;
    U32 memTestsOnly = 0;
    const char* const programName = argv[0];

    /* Check command line */
    for (argNb=1; argNb<argc; argNb++) {
        const char* argument = argv[argNb];
        if(!argument) continue;   /* Protection if argument empty */

        /* Handle commands. Aggregated commands are allowed */
        if (argument[0]=='-') {

            if (longCommandWArg(&argument, "--memtest=")) { memTestsOnly = readU32FromChar(&argument); continue; }

            if (!strcmp(argument, "--memtest")) { memTestsOnly=1; continue; }
            if (!strcmp(argument, "--no-big-tests")) { bigTests=0; continue; }

            argument++;
            while (*argument!=0) {
                switch(*argument)
                {
                case 'h':
                    return FUZ_usage(programName);

                case 'v':
                    argument++;
                    g_displayLevel++;
                    break;

                case 'q':
                    argument++;
                    g_displayLevel--;
                    break;

                case 'p': /* pause at the end */
                    argument++;
                    mainPause = 1;
                    break;

                case 'i':
                    argument++; maxDuration = 0;
                    nbTests = (int)readU32FromChar(&argument);
                    break;

                case 'T':
                    argument++;
                    nbTests = 0;
                    maxDuration = readU32FromChar(&argument);
                    if (*argument=='s') argument++;   /* seconds */
                    if (*argument=='m') maxDuration *= 60, argument++;   /* minutes */
                    if (*argument=='n') argument++;
                    break;

                case 's':
                    argument++;
                    seedset = 1;
                    seed = readU32FromChar(&argument);
                    break;

                case 't':
                    argument++;
                    testNb = (int)readU32FromChar(&argument);
                    break;

                case 'P':   /* compressibility % */
                    argument++;
                    proba = (int)readU32FromChar(&argument);
                    if (proba>100) proba = 100;
                    break;

                default:
                    return (FUZ_usage(programName), 1);
    }   }   }   }   /* for (argNb=1; argNb<argc; argNb++) */

    /* Get Seed */
    DISPLAY("Starting zstd tester (%i-bits, %s)\n", (int)(sizeof(size_t)*8), ZSTD_VERSION_STRING);

    if (!seedset) {
        time_t const t = time(NULL);
        U32 const h = XXH32(&t, sizeof(t), 1);
        seed = h % 10000;
    }

    DISPLAY("Seed = %u\n", (unsigned)seed);
    if (proba!=FUZ_compressibility_default) DISPLAY("Compressibility : %i%%\n", proba);

    if (memTestsOnly) {
        g_displayLevel = MAX(3, g_displayLevel);
        return FUZ_mallocTests(seed, ((double)proba) / 100, memTestsOnly);
    }

    if (nbTests < testNb) nbTests = testNb;

    if (testNb==0)
        result = basicUnitTests(0, ((double)proba) / 100);  /* constant seed for predictability */
    if (!result)
        result = fuzzerTests(seed, nbTests, testNb, maxDuration, ((double)proba) / 100, bigTests);
    if (mainPause) {
        int unused;
        DISPLAY("Press Enter \n");
        unused = getchar();
        (void)unused;
    }
    return result;
}