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
 int COMPRESSIBILITY_DEFAULT ; 
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 scalar_t__ g_timeLimit_s ; 

__attribute__((used)) static int usage_advanced(void)
{
    DISPLAY( "\nAdvanced options :\n");
    DISPLAY( " -T#          : set level 1 speed objective \n");
    DISPLAY( " -B#          : cut input into blocks of size # (default : single block) \n");
    DISPLAY( " --optimize=  : same as -O with more verbose syntax (see README.md)\n");
    DISPLAY( " -S           : Single run \n");
    DISPLAY( " --zstd       : Single run, parameter selection same as zstdcli \n");
    DISPLAY( " -P#          : generated sample compressibility (default : %.1f%%) \n", COMPRESSIBILITY_DEFAULT * 100);
    DISPLAY( " -t#          : Caps runtime of operation in seconds (default : %u seconds (%.1f hours)) \n",
                                (unsigned)g_timeLimit_s, (double)g_timeLimit_s / 3600);
    DISPLAY( " -v           : Prints Benchmarking output\n");
    DISPLAY( " -D           : Next argument dictionary file\n");
    DISPLAY( " -s           : Seperate Files\n");
    return 0;
}