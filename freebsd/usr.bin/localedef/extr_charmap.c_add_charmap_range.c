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
 int /*<<< orphan*/  add_charmap_impl (char*,int,int) ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*,int,int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  errf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int strcspn (char*,char const*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ strspn (char*,char const*) ; 

void
add_charmap_range(char *s, char *e, int wc)
{
	int	ls, le;
	int	si;
	int	sn, en;
	int	i;

	static const char *digits = "0123456789";

	ls = strlen(s);
	le = strlen(e);

	if (((si = strcspn(s, digits)) == 0) || (si == ls) ||
	    (strncmp(s, e, si) != 0) ||
	    ((int)strspn(s + si, digits) != (ls - si)) ||
	    ((int)strspn(e + si, digits) != (le - si)) ||
	    ((sn = atoi(s + si)) > ((en = atoi(e + si))))) {
		errf("malformed charmap range");
		return;
	}

	s[si] = 0;

	for (i = sn; i <= en; i++) {
		char *nn;
		(void) asprintf(&nn, "%s%0*u", s, ls - si, i);
		if (nn == NULL) {
			errf("out of memory");
			return;
		}

		add_charmap_impl(nn, wc, 1);
		wc++;
	}
	free(s);
	free(e);
}