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

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_DISPLAY_LEVEL ; 
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 char* WELCOME_MESSAGE ; 
 int /*<<< orphan*/  ZSTDCLI_CLEVEL_DEFAULT ; 

__attribute__((used)) static int usage(const char* programName)
{
    DISPLAY(WELCOME_MESSAGE);
    DISPLAY( "Usage :\n");
    DISPLAY( "      %s [args] [FILE(s)] [-o file]\n", programName);
    DISPLAY( "\n");
    DISPLAY( "FILE    : a filename\n");
    DISPLAY( "          with no FILE, or when FILE is - , read standard input\n");
    DISPLAY( "Arguments :\n");
    DISPLAY( " -D file: use `file` as Dictionary \n");
    DISPLAY( " -h/-H  : display help/long help and exit\n");
    DISPLAY( " -V     : display Version number and exit\n");
    DISPLAY( " -v     : verbose mode; specify multiple times to increase log level (default:%d)\n", DEFAULT_DISPLAY_LEVEL);
    DISPLAY( " -q     : suppress warnings; specify twice to suppress errors too\n");
#ifdef UTIL_HAS_CREATEFILELIST
    DISPLAY( " -r     : operate recursively on directories\n");
#endif
    DISPLAY( "\n");
    DISPLAY( "Benchmark arguments :\n");
    DISPLAY( " -b#    : benchmark file(s), using # compression level (default : %d) \n", ZSTDCLI_CLEVEL_DEFAULT);
    DISPLAY( " -e#    : test all compression levels from -bX to # (default: %d)\n", ZSTDCLI_CLEVEL_DEFAULT);
    DISPLAY( " -i#    : minimum evaluation time in seconds (default : 3s)\n");
    DISPLAY( " -B#    : cut file into independent blocks of size # (default: no block)\n");
    return 0;
}