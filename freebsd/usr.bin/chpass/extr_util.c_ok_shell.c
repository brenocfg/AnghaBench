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
 char* strrchr (char*,char) ; 

int
ok_shell(char *name)
{
	char *p, *sh;

	setusershell();
	while ((sh = getusershell())) {
		if (!strcmp(name, sh)) {
			endusershell();
			return (1);
		}
		/* allow just shell name, but use "real" path */
		if ((p = strrchr(sh, '/')) && strcmp(name, p + 1) == 0) {
			endusershell();
			return (1);
		}
	}
	endusershell();
	return (0);
}