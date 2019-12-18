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
 int EX_USAGE ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  be ; 
 int /*<<< orphan*/  be_export (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int usage (int) ; 

__attribute__((used)) static int
bectl_cmd_export(int argc, char *argv[])
{
	char *bootenv;

	if (argc == 1) {
		fprintf(stderr, "bectl export: missing boot environment name\n");
		return (usage(false));
	}

	if (argc > 2) {
		fprintf(stderr, "bectl export: extra arguments provided\n");
		return (usage(false));
	}

	bootenv = argv[1];

	if (isatty(STDOUT_FILENO)) {
		fprintf(stderr, "bectl export: must redirect output\n");
		return (EX_USAGE);
	}

	be_export(be, bootenv, STDOUT_FILENO);

	return (0);
}