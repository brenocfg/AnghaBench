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
 int /*<<< orphan*/  ISASCII (char) ; 
 scalar_t__ is_unique (char*,char**,char**) ; 
 scalar_t__ islower (unsigned char) ; 
 scalar_t__ malloc (int) ; 
 char* name_unknown ; 
 int strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  strupr (char*) ; 
 char toupper (unsigned char) ; 
 char** unknown ; 

__attribute__((used)) static char **
mklist(char *buf, char *name)
{
	int n;
	char c, *cp, **argvp, *cp2, **argv, **avt;

	if (name) {
		if ((int)strlen(name) > 40) {
			name = 0;
			unknown[0] = name_unknown;
		} else {
			unknown[0] = name;
			strupr(name);
		}
	} else
		unknown[0] = name_unknown;
	/*
	 * Count up the number of names.
	 */
	for (n = 1, cp = buf; *cp && *cp != ':'; cp++) {
		if (*cp == '|')
			n++;
	}
	/*
	 * Allocate an array to put the name pointers into
	 */
	argv = (char **)malloc((n+3)*sizeof(char *));
	if (argv == 0)
		return(unknown);

	/*
	 * Fill up the array of pointers to names.
	 */
	*argv = 0;
	argvp = argv+1;
	n = 0;
	for (cp = cp2 = buf; (c = *cp);  cp++) {
		if (c == '|' || c == ':') {
			*cp++ = '\0';
			/*
			 * Skip entries that have spaces or are over 40
			 * characters long.  If this is our environment
			 * name, then put it up front.  Otherwise, as
			 * long as this is not a duplicate name (case
			 * insensitive) add it to the list.
			 */
			if (n || (cp - cp2 > 41))
				;
			else if (name && (strncasecmp(name, cp2, cp-cp2) == 0))
				*argv = cp2;
			else if (is_unique(cp2, argv+1, argvp))
				*argvp++ = cp2;
			if (c == ':')
				break;
			/*
			 * Skip multiple delimiters. Reset cp2 to
			 * the beginning of the next name. Reset n,
			 * the flag for names with spaces.
			 */
			while ((c = *cp) == '|')
				cp++;
			cp2 = cp;
			n = 0;
		}
		/*
		 * Skip entries with spaces or non-ascii values.
		 * Convert lower case letters to upper case.
		 */
#undef ISASCII
#define ISASCII(c) (!((c)&0x80))
		if ((c == ' ') || !ISASCII(c))
			n = 1;
		else if (islower((unsigned char)c))
			*cp = toupper((unsigned char)c);
	}

	/*
	 * Check for an old V6 2 character name.  If the second
	 * name points to the beginning of the buffer, and is
	 * only 2 characters long, move it to the end of the array.
	 */
	if ((argv[1] == buf) && (strlen(argv[1]) == 2)) {
		--argvp;
		for (avt = &argv[1]; avt < argvp; avt++)
			*avt = *(avt+1);
		*argvp++ = buf;
	}

	/*
	 * Duplicate last name, for TTYPE option, and null
	 * terminate the array.  If we didn't find a match on
	 * our terminal name, put that name at the beginning.
	 */
	cp = *(argvp-1);
	*argvp++ = cp;
	*argvp = 0;

	if (*argv == 0) {
		if (name)
			*argv = name;
		else {
			--argvp;
			for (avt = argv; avt < argvp; avt++)
				*avt = *(avt+1);
		}
	}
	if (*argv)
		return(argv);
	else
		return(unknown);
}