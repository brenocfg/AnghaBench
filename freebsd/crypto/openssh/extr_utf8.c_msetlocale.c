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
 int /*<<< orphan*/  LC_CTYPE ; 
 char* getenv (char const*) ; 
 int /*<<< orphan*/ * setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * strcasestr (char*,char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

void
msetlocale(void)
{
	const char *vars[] = { "LC_ALL", "LC_CTYPE", "LANG", NULL };
	char *cp;
	int i;

	/*
	 * We can't yet cope with dotless/dotted I in Turkish locales,
	 * so fall back to the C locale for these.
	 */
	for (i = 0; vars[i] != NULL; i++) {
		if ((cp = getenv(vars[i])) == NULL)
			continue;
		if (strncasecmp(cp, "TR", 2) != 0)
			break;
		/*
		 * If we're in a UTF-8 locale then prefer to use
		 * the C.UTF-8 locale (or equivalent) if it exists.
		 */
		if ((strcasestr(cp, "UTF-8") != NULL ||
		    strcasestr(cp, "UTF8") != NULL) &&
		    (setlocale(LC_CTYPE, "C.UTF-8") != NULL ||
		    setlocale(LC_CTYPE, "POSIX.UTF-8") != NULL))
			return;
		setlocale(LC_CTYPE, "C");
		return;
	}
	/* We can handle this locale */
	setlocale(LC_CTYPE, "");
}