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
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  be ; 
 int be_import (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int usage (int) ; 

__attribute__((used)) static int
bectl_cmd_import(int argc, char *argv[])
{
	char *bootenv;
	int err;

	if (argc == 1) {
		fprintf(stderr, "bectl import: missing boot environment name\n");
		return (usage(false));
	}

	if (argc > 2) {
		fprintf(stderr, "bectl import: extra arguments provided\n");
		return (usage(false));
	}

	bootenv = argv[1];

	if (isatty(STDIN_FILENO)) {
		fprintf(stderr, "bectl import: input can not be from terminal\n");
		return (EX_USAGE);
	}

	err = be_import(be, bootenv, STDIN_FILENO);

	return (err);
}