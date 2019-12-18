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
 int /*<<< orphan*/  D (char*,char*,char const*,char**) ; 
 int /*<<< orphan*/  DX (int,char*,...) ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long
getnum(const char *s, char **next, const char *key)
{
	char *end = NULL;
	long l;

	if (next)	/* default */
		*next = NULL;
	if (s && *s) {
		DX(3, "token is <%s> %s", s, key ? key : "-");
		l = strtol(s, &end, 0);
	} else {
		DX(3, "empty string");
		l = -1;
	}
	if (l < 0) {
		DX(2, "invalid %s for %s", s ? s : "NULL", (key ? key : "") );
		return 0;	// invalid 
	}
	if (!end || !*end)
		return l;
	if (*end == 'n')
		l = -l;	/* multiply by n */
	else if (*end == 'K')
		l = l*1000;
	else if (*end == 'M')
		l = l*1000000;
	else if (*end == 'k')
		l = l*1024;
	else if (*end == 'm')
		l = l*1024*1024;
	else if (*end == 'w')
		;
	else {/* not recognized */
		D("suffix %s for %s, next %p", end, key, next);
		end--;
	}
	end++;
	DX(3, "suffix now %s for %s, next %p", end, key, next);
	if (next && *end) {
		DX(3, "setting next to %s for %s", end, key);
		*next = end;
	}
	return l;
}