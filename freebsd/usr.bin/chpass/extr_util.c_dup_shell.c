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
 int /*<<< orphan*/  endusershell () ; 
 char* getusershell () ; 
 int /*<<< orphan*/  setusershell () ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 char* strrchr (char*,char) ; 

char *
dup_shell(char *name)
{
	char *p, *sh, *ret;

	setusershell();
	while ((sh = getusershell())) {
		if (!strcmp(name, sh)) {
			endusershell();
			return (strdup(name));
		}
		/* allow just shell name, but use "real" path */
		if ((p = strrchr(sh, '/')) && strcmp(name, p + 1) == 0) {
			ret = strdup(sh);
			endusershell();
			return (ret);
		}
	}
	endusershell();
	return (NULL);
}