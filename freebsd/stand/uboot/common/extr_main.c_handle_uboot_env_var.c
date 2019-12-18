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
typedef  int /*<<< orphan*/  ldvar ;
typedef  enum ubenv_action { ____Placeholder_ubenv_action } ubenv_action ;

/* Variables and functions */
 int MIN (int,int) ; 
 int UBENV_IMPORT ; 
 int UBENV_SHOW ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setenv (char*,char const*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strcspn (char const*,char*) ; 
 int /*<<< orphan*/  strncat (char*,char const*,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* ub_env_get (char const*) ; 

__attribute__((used)) static void
handle_uboot_env_var(enum ubenv_action action, const char * var)
{
	char ldvar[128];
	const char *val;
	char *wrk;
	int len;

	/*
	 * On an import with the variable name formatted as ldname=ubname,
	 * import the uboot variable ubname into the loader variable ldname,
	 * otherwise the historical behavior is to import to uboot.ubname.
	 */
	if (action == UBENV_IMPORT) { 
		len = strcspn(var, "=");
		if (len == 0) {
			printf("name cannot start with '=': '%s'\n", var);
			return;
		}
		if (var[len] == 0) {
			strcpy(ldvar, "uboot.");
			strncat(ldvar, var, sizeof(ldvar) - 7);
		} else {
			len = MIN(len, sizeof(ldvar) - 1);
			strncpy(ldvar, var, len);
			ldvar[len] = 0;
			var = &var[len + 1];
		}
	}

	/*
	 * If the user prepended "uboot." (which is how they usually see these
	 * names) strip it off as a convenience.
	 */
	if (strncmp(var, "uboot.", 6) == 0) {
		var = &var[6];
	}

	/* If there is no variable name left, punt. */
	if (var[0] == 0) {
		printf("empty variable name\n");
		return;
	}

	val = ub_env_get(var);
	if (action == UBENV_SHOW) {
		if (val == NULL)
			printf("uboot.%s is not set\n", var);
		else
			printf("uboot.%s=%s\n", var, val);
	} else if (action == UBENV_IMPORT) {
		if (val != NULL) {
			setenv(ldvar, val, 1);
		}
	}
}