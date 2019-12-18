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
 int /*<<< orphan*/  FNM_CASEFOLD ; 
 scalar_t__ fnmatch (char*,char const*,int /*<<< orphan*/ ) ; 
 char* matchline ; 
 int strcspn (char*,char*) ; 
 int strspn (char*,char*) ; 

__attribute__((used)) static int
check_match(const char *ifname) 
{
	char *p = matchline, *c, t;
	int match = 0, mlen;
	
	if (matchline == NULL)
		return (0);

	/* Strip leading whitespaces */
	while (*p == ' ')
		p ++;

	c = p;
	while ((mlen = strcspn(c, " ;,")) != 0) {
		p = c + mlen;
		t = *p;
		if (p - c > 0) {
			*p = '\0';
			if (fnmatch(c, ifname, FNM_CASEFOLD) == 0) {
				*p = t;
				return (1);
			}
			*p = t;
			c = p + strspn(p, " ;,");
		}
		else {
			c = p + strspn(p, " ;,");
		}
	}

	return (match);
}