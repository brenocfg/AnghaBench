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
typedef  enum ubenv_action { ____Placeholder_ubenv_action } ubenv_action ;

/* Variables and functions */
 int CMD_ERROR ; 
 int CMD_OK ; 
 int UBENV_IMPORT ; 
 int UBENV_SHOW ; 
 int UBENV_UNKNOWN ; 
 char* command_errmsg ; 
 int /*<<< orphan*/  handle_uboot_env_var (int,char const*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 char* ub_env_enum (char const*) ; 

__attribute__((used)) static int
command_ubenv(int argc, char *argv[])
{
	enum ubenv_action action;
	const char *var;
	int i;

	action = UBENV_UNKNOWN;
	if (argc > 1) {
		if (strcasecmp(argv[1], "import") == 0)
			action = UBENV_IMPORT;
		else if (strcasecmp(argv[1], "show") == 0)
			action = UBENV_SHOW;
	}
	if (action == UBENV_UNKNOWN) {
		command_errmsg = "usage: 'ubenv <import|show> [var ...]";
		return (CMD_ERROR);
	}

	if (argc > 2) {
		for (i = 2; i < argc; i++)
			handle_uboot_env_var(action, argv[i]);
	} else {
		var = NULL;
		for (;;) {
			if ((var = ub_env_enum(var)) == NULL)
				break;
			handle_uboot_env_var(action, var);
		}
	}

	return (CMD_OK);
}