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
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ isspace (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/ * strpbrk (char*,char*) ; 
 char* strsep (char**,char*) ; 

void
wrtermcap(char *bp)
{
	register int ch;
	register char *p;
	char *t, *sep;

	/* Find the end of the terminal names. */
	if ((t = strchr(bp, ':')) == NULL)
		errx(1, "termcap names not colon terminated");
	*t++ = '\0';

	/* Output terminal names that don't have whitespace. */
	sep = strdup("");
	while ((p = strsep(&bp, "|")) != NULL)
		if (*p != '\0' && strpbrk(p, " \t") == NULL) {
			(void)printf("%s%s", sep, p);
			sep = strdup("|");
		}
	(void)putchar(':');

	/*
	 * Output fields, transforming any dangerous characters.  Skip
	 * empty fields or fields containing only whitespace.
	 */
	while ((p = strsep(&t, ":")) != NULL) {
		while ((ch = *p) != '\0' && isspace(ch))
			++p;
		if (ch == '\0')
			continue;
		while ((ch = *p++) != '\0')
			switch(ch) {
			case '\033':
				(void)printf("\\E");
			case  ' ':		/* No spaces. */
				(void)printf("\\040");
				break;
			case '!':		/* No csh history chars. */
				(void)printf("\\041");
				break;
			case ',':		/* No csh history chars. */
				(void)printf("\\054");
				break;
			case '"':		/* No quotes. */
				(void)printf("\\042");
				break;
			case '\'':		/* No quotes. */
				(void)printf("\\047");
				break;
			case '`':		/* No quotes. */
				(void)printf("\\140");
				break;
			case '\\':		/* Anything following is OK. */
			case '^':
				(void)putchar(ch);
				if ((ch = *p++) == '\0')
					break;
				/* FALLTHROUGH */
			default:
				(void)putchar(ch);
		}
		(void)putchar(':');
	}
}