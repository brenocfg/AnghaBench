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
 int /*<<< orphan*/  A_CONTINUE ; 
 int /*<<< orphan*/  A_PANIC ; 
 int /*<<< orphan*/  A_REBOOT ; 
 int /*<<< orphan*/  A_RETRY ; 
 int EINVAL ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int parse_token (char**,char**) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  root_mount_onfail ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int
parse_dir_onfail(char **conf)
{
	char *action;
	int error;

	error = parse_token(conf, &action);
	if (error)
		return (error);

	if (!strcmp(action, "continue"))
		root_mount_onfail = A_CONTINUE;
	else if (!strcmp(action, "panic"))
		root_mount_onfail = A_PANIC;
	else if (!strcmp(action, "reboot"))
		root_mount_onfail = A_REBOOT;
	else if (!strcmp(action, "retry"))
		root_mount_onfail = A_RETRY;
	else {
		printf("rootmount: %s: unknown action\n", action);
		error = EINVAL;
	}

	free(action, M_TEMP);
	return (0);
}