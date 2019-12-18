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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 

void usage(int status)
{
	FILE *stream = (status != EXIT_SUCCESS) ? stderr : stdout;

	fprintf(stream, "Usage: %s [OPTIONS...]\n", progname);
	fprintf(stream,
"\n"
"Options:\n"
"  -a <platform>   set platform to <platform>\n"
"  -b <brand>      set brand to <brand>\n"
"  -c <base1>\n"
"  -d <base2>\n"
"  -f <flag>       set flag to <flag>\n"
"  -i <file>       read input from the file <file>\n"
"  -I <file>       read input from the file <file> for DHP series\n"
"  -l <language>   set language to <language>\n"
"  -m <version>    set minor version to <version>\n"
"  -o <file>       write output to the file <file>\n"
"  -p <product>    set product to <product>\n"
"  -r <region>     set image region to <region>\n"
"		   valid regions: JP, US, EU, AP, TW, KR, M_\n"
"  -s              skip CRC calculation\n"
"  -v <version>    set major version to <version>\n"
"  -w <version>    set harwdware version to <version>\n"
"  -h              show this screen\n"
	);

	exit(status);
}