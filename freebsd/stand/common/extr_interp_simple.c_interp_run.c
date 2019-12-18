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
 int CMD_ERROR ; 
 int CMD_OK ; 
 char* command_errmsg ; 
 int /*<<< orphan*/  free (char**) ; 
 scalar_t__ interp_builtin_cmd (int,char**) ; 
 scalar_t__ parse (int*,char***,char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
interp_run(const char *input)
{
	int			argc;
	char			**argv;

	if (parse(&argc, &argv, input)) {
		printf("parse error\n");
		return CMD_ERROR;
	}

	if (interp_builtin_cmd(argc, argv)) {
		printf("%s: %s\n", argv[0], command_errmsg);
		free(argv);
		return CMD_ERROR;
	}
	free(argv);
	return CMD_OK;
}