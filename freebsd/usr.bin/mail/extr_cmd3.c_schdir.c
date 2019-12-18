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
 scalar_t__ chdir (char*) ; 
 char* expand (char*) ; 
 char* homedir ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
schdir(void *v)
{
	char **arglist = v;
	char *cp;

	if (*arglist == NULL) {
		if (homedir == NULL)
			return (1);
		cp = homedir;
	} else
		if ((cp = expand(*arglist)) == NULL)
			return (1);
	if (chdir(cp) < 0) {
		warn("%s", cp);
		return (1);
	}
	return (0);
}