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
struct tm {int tm_mon; } ;

/* Variables and functions */
 int /*<<< orphan*/ * strptime (char const*,char*,struct tm*) ; 
 scalar_t__ strtol (char const*,char**,int) ; 

__attribute__((used)) static int
parsemonth(const char *s, int *m, int *y)
{
	int nm, ny;
	char *cp;
	struct tm tm;

	nm = (int)strtol(s, &cp, 10);
	if (cp != s) {
		ny = *y;
		if (*cp == '\0') {
			;	/* no special action */
		} else if (*cp == 'f' || *cp == 'F') {
			if (nm <= *m)
				ny++;
		} else if (*cp == 'p' || *cp == 'P') {
			if (nm >= *m)
				ny--;
		} else
			return (1);
		if (nm < 1 || nm > 12)
			return 1;
		*m = nm;
		*y = ny;
		return (0);
	}
	if (strptime(s, "%B", &tm) != NULL || strptime(s, "%b", &tm) != NULL) {
		*m = tm.tm_mon + 1;
		return (0);
	}
	return (1);
}