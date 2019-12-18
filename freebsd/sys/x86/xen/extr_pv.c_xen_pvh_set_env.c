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
 scalar_t__ kern_setenv (char*,char*) ; 
 int strlen (char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  xc_printf (char*,char*,char*) ; 

__attribute__((used)) static void
xen_pvh_set_env(char *env, bool (*filter)(const char *))
{
	char *option;

	if (env == NULL)
		return;

	option = env;
	while (*option != 0) {
		char *value;

		if (filter != NULL && filter(option)) {
			option += strlen(option) + 1;
			continue;
		}

		value = option;
		option = strsep(&value, "=");
		if (kern_setenv(option, value) != 0)
			xc_printf("unable to add kenv %s=%s\n", option, value);
		option = value + strlen(value) + 1;
	}
}