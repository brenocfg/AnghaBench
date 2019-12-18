#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  parsedLine ;
typedef  int /*<<< orphan*/  XXH64_hash_t ;
typedef  int /*<<< orphan*/  XXH32_hash_t ;
struct TYPE_8__ {int /*<<< orphan*/  xxh64; int /*<<< orphan*/  xxh32; } ;
struct TYPE_9__ {int quit; scalar_t__ xxhBits; int /*<<< orphan*/  filename; int /*<<< orphan*/  nMismatchedChecksums; int /*<<< orphan*/  nOpenOrReadFailures; TYPE_1__ canonical; int /*<<< orphan*/  nProperlyFormattedLines; int /*<<< orphan*/  nMixedFormatLines; int /*<<< orphan*/  nImproperlyFormattedLines; } ;
struct TYPE_10__ {char* inFileName; int /*<<< orphan*/  statusOnly; int /*<<< orphan*/  quiet; int /*<<< orphan*/  blockSize; int /*<<< orphan*/  blockBuf; scalar_t__ warn; int /*<<< orphan*/  lineBuf; int /*<<< orphan*/  inFile; int /*<<< orphan*/  lineMax; TYPE_2__ report; } ;
typedef  TYPE_2__ ParsedLine ;
typedef  TYPE_2__ ParseFileReport ;
typedef  TYPE_4__ ParseFileArg ;
typedef  int LineStatus ;
typedef  int GetLineResult ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BMK_hashStream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DISPLAY (char*,char const* const,...) ; 
 int /*<<< orphan*/  DISPLAYRESULT (char*,char const* const,...) ; 
#define  GetLine_eof 134 
#define  GetLine_exceedMaxLineLength 133 
#define  GetLine_ok 132 
#define  GetLine_outOfMemory 131 
#define  LineStatus_failedToOpen 130 
#define  LineStatus_hashFailed 129 
#define  LineStatus_hashOk 128 
 scalar_t__ ParseLine_ok ; 
 int /*<<< orphan*/  XXH32_hashFromCanonical (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XXH64_hashFromCanonical (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  algo_xxh32 ; 
 int /*<<< orphan*/  algo_xxh64 ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int getLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__* const,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parseLine (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parseFile1(ParseFileArg* parseFileArg)
{
    const char* const inFileName = parseFileArg->inFileName;
    ParseFileReport* const report = &parseFileArg->report;

    unsigned long lineNumber = 0;
    memset(report, 0, sizeof(*report));

    while (!report->quit) {
        FILE* fp = NULL;
        LineStatus lineStatus = LineStatus_hashFailed;
        GetLineResult getLineResult;
        ParsedLine parsedLine;
        memset(&parsedLine, 0, sizeof(parsedLine));

        lineNumber++;
        if (lineNumber == 0) {
            /* This is unlikely happen, but md5sum.c has this
             * error check. */
            DISPLAY("%s : too many checksum lines\n", inFileName);
            report->quit = 1;
            break;
        }

        getLineResult = getLine(&parseFileArg->lineBuf, &parseFileArg->lineMax,
                                parseFileArg->inFile);
        if (getLineResult != GetLine_ok) {
            if (getLineResult == GetLine_eof) break;

            switch (getLineResult)
            {
            case GetLine_ok:
            case GetLine_eof:
                /* These cases never happen.  See above getLineResult related "if"s.
                   They exist just for make gcc's -Wswitch-enum happy. */
                break;

            default:
                DISPLAY("%s : %lu: unknown error\n", inFileName, lineNumber);
                break;

            case GetLine_exceedMaxLineLength:
                DISPLAY("%s : %lu: too long line\n", inFileName, lineNumber);
                break;

            case GetLine_outOfMemory:
                DISPLAY("%s : %lu: out of memory\n", inFileName, lineNumber);
                break;
            }
            report->quit = 1;
            break;
        }

        if (parseLine(&parsedLine, parseFileArg->lineBuf) != ParseLine_ok) {
            report->nImproperlyFormattedLines++;
            if (parseFileArg->warn) {
                DISPLAY("%s : %lu: improperly formatted XXHASH checksum line\n"
                    , inFileName, lineNumber);
            }
            continue;
        }

        if (report->xxhBits != 0 && report->xxhBits != parsedLine.xxhBits) {
            /* Don't accept xxh32/xxh64 mixed file */
            report->nImproperlyFormattedLines++;
            report->nMixedFormatLines++;
            if (parseFileArg->warn) {
                DISPLAY("%s : %lu: improperly formatted XXHASH checksum line (XXH32/64)\n"
                    , inFileName, lineNumber);
            }
            continue;
        }

        report->nProperlyFormattedLines++;
        if (report->xxhBits == 0) {
            report->xxhBits = parsedLine.xxhBits;
        }

        fp = fopen(parsedLine.filename, "rb");
        if (fp == NULL) {
            lineStatus = LineStatus_failedToOpen;
        } else {
            lineStatus = LineStatus_hashFailed;
            switch (parsedLine.xxhBits)
            {
            case 32:
                {   XXH32_hash_t xxh;
                    BMK_hashStream(&xxh, algo_xxh32, fp, parseFileArg->blockBuf, parseFileArg->blockSize);
                    if (xxh == XXH32_hashFromCanonical(&parsedLine.canonical.xxh32)) {
                        lineStatus = LineStatus_hashOk;
                }   }
                break;

            case 64:
                {   XXH64_hash_t xxh;
                    BMK_hashStream(&xxh, algo_xxh64, fp, parseFileArg->blockBuf, parseFileArg->blockSize);
                    if (xxh == XXH64_hashFromCanonical(&parsedLine.canonical.xxh64)) {
                        lineStatus = LineStatus_hashOk;
                }   }
                break;

            default:
                break;
            }
            fclose(fp);
        }

        switch (lineStatus)
        {
        default:
            DISPLAY("%s : unknown error\n", inFileName);
            report->quit = 1;
            break;

        case LineStatus_failedToOpen:
            report->nOpenOrReadFailures++;
            if (!parseFileArg->statusOnly) {
                DISPLAYRESULT("%s : %lu: FAILED open or read %s\n"
                    , inFileName, lineNumber, parsedLine.filename);
            }
            break;

        case LineStatus_hashOk:
        case LineStatus_hashFailed:
            {   int b = 1;
                if (lineStatus == LineStatus_hashOk) {
                    /* If --quiet is specified, don't display "OK" */
                    if (parseFileArg->quiet) b = 0;
                } else {
                    report->nMismatchedChecksums++;
                }

                if (b && !parseFileArg->statusOnly) {
                    DISPLAYRESULT("%s: %s\n", parsedLine.filename
                        , lineStatus == LineStatus_hashOk ? "OK" : "FAILED");
            }   }
            break;
        }
    }   /* while (!report->quit) */
}