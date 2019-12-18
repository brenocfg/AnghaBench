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
 int /*<<< orphan*/  PS_OPT_VERBOSE ; 
 int getopt (int,char* const*,char*) ; 
 int /*<<< orphan*/  procstat_opts ; 
 int /*<<< orphan*/  usage () ; 

void
cmdopt_verbose(int argc, char * const argv[])
{
	int ch;

	while ((ch = getopt(argc, argv, "v")) != -1) {
		switch (ch) {
		case 'v':
			procstat_opts |= PS_OPT_VERBOSE;
			break;
		case '?':
		default:
			usage();
		}
	}
}