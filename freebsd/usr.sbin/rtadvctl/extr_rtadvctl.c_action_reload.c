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
 int action_propset (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static int
action_reload(int argc, char **argv)
{
	char *action_argv;
	char argv_reload[IFNAMSIZ + sizeof(":reload=")];
	int i;
	int error;

	if (argc == 0) {
		action_argv = strdup(":reload=");
		return (action_propset(action_argv));
	}

	error = 0;
	for (i = 0; i < argc; i++) {
		sprintf(argv_reload, "%s:reload=", argv[i]);
		action_argv = argv_reload;
		error += action_propset(action_argv);
	}

	return (error);
}