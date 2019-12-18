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
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ ) ; 
 int IN_NONE ; 
 int IN_SOME ; 
 int IN_THIS ; 
 int /*<<< orphan*/  YEAR_2000_NAME ; 
 char* _fmt (char*,struct tm const*,char*,char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tzset () ; 

size_t
strftime_l(char * __restrict s, size_t maxsize, const char * __restrict format,
    const struct tm * __restrict t, locale_t loc)
{
	char *	p;
	int	warn;
	FIX_LOCALE(loc);

	tzset();
	warn = IN_NONE;
	p = _fmt(((format == NULL) ? "%c" : format), t, s, s + maxsize, &warn, loc);
#ifndef NO_RUN_TIME_WARNINGS_ABOUT_YEAR_2000_PROBLEMS_THANK_YOU
	if (warn != IN_NONE && getenv(YEAR_2000_NAME) != NULL) {
		(void) fprintf_l(stderr, loc, "\n");
		if (format == NULL)
			(void) fputs("NULL strftime format ", stderr);
		else	(void) fprintf_l(stderr, loc, "strftime format \"%s\" ",
				format);
		(void) fputs("yields only two digits of years in ", stderr);
		if (warn == IN_SOME)
			(void) fputs("some locales", stderr);
		else if (warn == IN_THIS)
			(void) fputs("the current locale", stderr);
		else	(void) fputs("all locales", stderr);
		(void) fputs("\n", stderr);
	}
#endif /* !defined NO_RUN_TIME_WARNINGS_ABOUT_YEAR_2000_PROBLEMS_THANK_YOU */
	if (p == s + maxsize)
		return (0);
	*p = '\0';
	return p - s;
}