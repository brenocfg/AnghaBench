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
 char** altnames ; 
 int argcount (char**) ; 
 void* calloc (unsigned int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

int
alternates(char **namelist)
{
	int c;
	char **ap, **ap2, *cp;

	c = argcount(namelist) + 1;
	if (c == 1) {
		if (altnames == 0)
			return (0);
		for (ap = altnames; *ap != NULL; ap++)
			printf("%s ", *ap);
		printf("\n");
		return (0);
	}
	if (altnames != 0)
		(void)free(altnames);
	if ((altnames = calloc((unsigned)c, sizeof(char *))) == NULL)
		err(1, "Out of memory");
	for (ap = namelist, ap2 = altnames; *ap != NULL; ap++, ap2++) {
		cp = calloc((unsigned)strlen(*ap) + 1, sizeof(char));
		strcpy(cp, *ap);
		*ap2 = cp;
	}
	*ap2 = 0;
	return (0);
}