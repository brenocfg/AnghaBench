#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ endianess ;
typedef  void* U32 ;
struct TYPE_4__ {scalar_t__ nProperlyFormattedLines; scalar_t__ nImproperlyFormattedLines; scalar_t__ nOpenOrReadFailures; scalar_t__ nMismatchedChecksums; scalar_t__ quit; } ;
struct TYPE_5__ {char const* inFileName; char* lineBuf; int blockSize; char* blockBuf; void* quiet; void* warn; void* statusOnly; void* strictMode; scalar_t__ lineMax; int /*<<< orphan*/ * inFile; TYPE_1__ report; } ;
typedef  TYPE_1__ ParseFileReport ;
typedef  TYPE_2__ ParseFileArg ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ DEFAULT_LINE_LENGTH ; 
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 int /*<<< orphan*/  DISPLAYRESULT (char*,scalar_t__) ; 
 scalar_t__ const big_endian ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  parseFile1 (TYPE_2__* const) ; 
 int /*<<< orphan*/ * stdin ; 
 char const* stdinName ; 

__attribute__((used)) static int checkFile(const char* inFileName,
                     const endianess displayEndianess,
                     U32 strictMode,
                     U32 statusOnly,
                     U32 warn,
                     U32 quiet)
{
    int result = 0;
    FILE* inFile = NULL;
    ParseFileArg parseFileArgBody;
    ParseFileArg* const parseFileArg = &parseFileArgBody;
    ParseFileReport* const report = &parseFileArg->report;

    if (displayEndianess != big_endian) {
        /* Don't accept little endian */
        DISPLAY( "Check file mode doesn't support little endian\n" );
        return 0;
    }

    /* note : stdinName is special constant pointer.  It is not a string. */
    if (inFileName == stdinName) {
        /* note : Since we expect text input for xxhash -c mode,
         * Don't set binary mode for stdin */
        inFile = stdin;
    } else {
        inFile = fopen( inFileName, "rt" );
    }

    if (inFile == NULL) {
        DISPLAY( "Pb opening %s\n", inFileName);
        return 0;
    }

    parseFileArg->inFileName    = inFileName;
    parseFileArg->inFile        = inFile;
    parseFileArg->lineMax       = DEFAULT_LINE_LENGTH;
    parseFileArg->lineBuf       = (char*) malloc((size_t) parseFileArg->lineMax);
    parseFileArg->blockSize     = 64 * 1024;
    parseFileArg->blockBuf      = (char*) malloc(parseFileArg->blockSize);
    parseFileArg->strictMode    = strictMode;
    parseFileArg->statusOnly    = statusOnly;
    parseFileArg->warn          = warn;
    parseFileArg->quiet         = quiet;

    parseFile1(parseFileArg);

    free(parseFileArg->blockBuf);
    free(parseFileArg->lineBuf);

    if (inFile != stdin) fclose(inFile);

    /* Show error/warning messages.  All messages are copied from md5sum.c
     */
    if (report->nProperlyFormattedLines == 0) {
        DISPLAY("%s: no properly formatted XXHASH checksum lines found\n", inFileName);
    } else if (!statusOnly) {
        if (report->nImproperlyFormattedLines) {
            DISPLAYRESULT("%lu lines are improperly formatted\n"
                , report->nImproperlyFormattedLines);
        }
        if (report->nOpenOrReadFailures) {
            DISPLAYRESULT("%lu listed files could not be read\n"
                , report->nOpenOrReadFailures);
        }
        if (report->nMismatchedChecksums) {
            DISPLAYRESULT("%lu computed checksums did NOT match\n"
                , report->nMismatchedChecksums);
    }   }

    /* Result (exit) code logic is copied from
     * gnu coreutils/src/md5sum.c digest_check() */
    result =   report->nProperlyFormattedLines != 0
            && report->nMismatchedChecksums == 0
            && report->nOpenOrReadFailures == 0
            && (!strictMode || report->nImproperlyFormattedLines == 0)
            && report->quit == 0;
    return result;
}