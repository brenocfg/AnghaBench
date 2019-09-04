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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  run_revision_walk () ; 
 int /*<<< orphan*/  setup_git_directory () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int cmd__revision_walking(int argc, const char **argv)
{
	if (argc < 2)
		return 1;

	setup_git_directory();

	if (!strcmp(argv[1], "run-twice")) {
		printf("1st\n");
		if (!run_revision_walk())
			return 1;
		printf("2nd\n");
		if (!run_revision_walk())
			return 1;

		return 0;
	}

	fprintf(stderr, "check usage\n");
	return 1;
}