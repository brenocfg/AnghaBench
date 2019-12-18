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
 int /*<<< orphan*/  __progname ; 
 int be_verbose ; 
 int compile_opts_only ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  showOptions () ; 
 int /*<<< orphan*/  ssh_get_progname (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  testAPI () ; 
 int /*<<< orphan*/  testOutput () ; 

int
main(int argc, char *argv[])
{
	printf("Platform-independent login recording test driver\n");

	__progname = ssh_get_progname(argv[0]);
	if (argc == 2) {
		if (strncmp(argv[1], "-i", 3) == 0)
			compile_opts_only = 1;
		else if (strncmp(argv[1], "-v", 3) == 0)
			be_verbose=1;
	}

	if (!compile_opts_only) {
		if (be_verbose && !testOutput())
			return 1;

		if (!testAPI())
			return 1;
	}

	showOptions();

	return 0;
}