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
 int /*<<< orphan*/  done (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

void
canon(char *rawname, char *canonname, size_t len)
{
	char *cp, *np;

	if (strcmp(rawname, ".") == 0 || strncmp(rawname, "./", 2) == 0)
		(void) strcpy(canonname, "");
	else if (rawname[0] == '/')
		(void) strcpy(canonname, ".");
	else
		(void) strcpy(canonname, "./");
	if (strlen(canonname) + strlen(rawname) >= len) {
		fprintf(stderr, "canonname: not enough buffer space\n");
		done(1);
	}
		
	(void) strcat(canonname, rawname);
	/*
	 * Eliminate multiple and trailing '/'s
	 */
	for (cp = np = canonname; *np != '\0'; cp++) {
		*cp = *np++;
		while (*cp == '/' && *np == '/')
			np++;
	}
	*cp = '\0';
	if (*--cp == '/')
		*cp = '\0';
	/*
	 * Eliminate extraneous "." and ".." from pathnames.
	 */
	for (np = canonname; *np != '\0'; ) {
		np++;
		cp = np;
		while (*np != '/' && *np != '\0')
			np++;
		if (np - cp == 1 && *cp == '.') {
			cp--;
			(void) strcpy(cp, np);
			np = cp;
		}
		if (np - cp == 2 && strncmp(cp, "..", 2) == 0) {
			cp--;
			while (cp > &canonname[1] && *--cp != '/')
				/* find beginning of name */;
			(void) strcpy(cp, np);
			np = cp;
		}
	}
}