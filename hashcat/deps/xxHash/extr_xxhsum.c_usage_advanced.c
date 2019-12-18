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
 int /*<<< orphan*/  g_nbIterations ; 
 int /*<<< orphan*/  usage (char const*) ; 

__attribute__((used)) static int usage_advanced(const char* exename)
{
    usage(exename);
    DISPLAY( "Advanced :\n");
    DISPLAY( " --little-endian : hash printed using little endian convention (default: big endian)\n");
    DISPLAY( " -V, --version   : display version\n");
    DISPLAY( " -h, --help      : display long help and exit\n");
    DISPLAY( " -b  : benchmark mode \n");
    DISPLAY( " -i# : number of iterations (benchmark mode; default %i)\n", g_nbIterations);
    DISPLAY( "\n");
    DISPLAY( "The following four options are useful only when verifying checksums (-c):\n");
    DISPLAY( "--strict : don't print OK for each successfully verified file\n");
    DISPLAY( "--status : don't output anything, status code shows success\n");
    DISPLAY( "--quiet  : exit non-zero for improperly formatted checksum lines\n");
    DISPLAY( "--warn   : warn about improperly formatted checksum lines\n");
    return 0;
}