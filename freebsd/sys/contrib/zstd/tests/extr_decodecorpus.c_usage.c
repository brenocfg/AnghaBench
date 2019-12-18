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
 int /*<<< orphan*/  DISPLAY (char*,...) ; 

__attribute__((used)) static void usage(const char* programName)
{
    DISPLAY( "Usage :\n");
    DISPLAY( "      %s [args]\n", programName);
    DISPLAY( "\n");
    DISPLAY( "Arguments :\n");
    DISPLAY( " -p<path> : select output path (default:stdout)\n");
    DISPLAY( "                in multiple files mode this should be a directory\n");
    DISPLAY( " -o<path> : select path to output original file (default:no output)\n");
    DISPLAY( "                in multiple files mode this should be a directory\n");
    DISPLAY( " -s#      : select seed (default:random based on time)\n");
    DISPLAY( " -n#      : number of files to generate (default:1)\n");
    DISPLAY( " -t       : activate test mode (test files against libzstd instead of outputting them)\n");
    DISPLAY( " -T#      : length of time to run tests for\n");
    DISPLAY( " -v       : increase verbosity level (default:0, max:7)\n");
    DISPLAY( " -h/H     : display help/long help and exit\n");
}