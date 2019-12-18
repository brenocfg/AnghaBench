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
struct fwdarg {char* arg; int ispath; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int
parse_fwd_field(char **p, struct fwdarg *fwd)
{
	char *ep, *cp = *p;
	int ispath = 0;

	if (*cp == '\0') {
		*p = NULL;
		return -1;	/* end of string */
	}

	/*
	 * A field escaped with square brackets is used literally.
	 * XXX - allow ']' to be escaped via backslash?
	 */
	if (*cp == '[') {
		/* find matching ']' */
		for (ep = cp + 1; *ep != ']' && *ep != '\0'; ep++) {
			if (*ep == '/')
				ispath = 1;
		}
		/* no matching ']' or not at end of field. */
		if (ep[0] != ']' || (ep[1] != ':' && ep[1] != '\0'))
			return -1;
		/* NUL terminate the field and advance p past the colon */
		*ep++ = '\0';
		if (*ep != '\0')
			*ep++ = '\0';
		fwd->arg = cp + 1;
		fwd->ispath = ispath;
		*p = ep;
		return 0;
	}

	for (cp = *p; *cp != '\0'; cp++) {
		switch (*cp) {
		case '\\':
			memmove(cp, cp + 1, strlen(cp + 1) + 1);
			if (*cp == '\0')
				return -1;
			break;
		case '/':
			ispath = 1;
			break;
		case ':':
			*cp++ = '\0';
			goto done;
		}
	}
done:
	fwd->arg = *p;
	fwd->ispath = ispath;
	*p = cp;
	return 0;
}