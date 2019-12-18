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
 int /*<<< orphan*/  IFNAMSIZ ; 
 scalar_t__ action_propset (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static int
action_enable(int argc, char **argv)
{
	char *action_argv;
	char argv_enable[IFNAMSIZ + sizeof(":enable=")];
	int i;
	int error;

	if (argc < 1)
		return (1);

	error = 0;
	for (i = 0; i < argc; i++) {
		sprintf(argv_enable, "%s:enable=", argv[i]);
		action_argv = argv_enable;
		error += action_propset(action_argv);
	}

	return (error);
}