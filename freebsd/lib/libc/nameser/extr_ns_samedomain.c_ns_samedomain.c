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
 size_t strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,size_t) ; 

int
ns_samedomain(const char *a, const char *b) {
	size_t la, lb;
	int diff, i, escaped;
	const char *cp;

	la = strlen(a);
	lb = strlen(b);

	/* Ignore a trailing label separator (i.e. an unescaped dot) in 'a'. */
	if (la != 0U && a[la - 1] == '.') {
		escaped = 0;
		/* Note this loop doesn't get executed if la==1. */
		for (i = la - 2; i >= 0; i--)
			if (a[i] == '\\') {
				if (escaped)
					escaped = 0;
				else
					escaped = 1;
			} else
				break;
		if (!escaped)
			la--;
	}

	/* Ignore a trailing label separator (i.e. an unescaped dot) in 'b'. */
	if (lb != 0U && b[lb - 1] == '.') {
		escaped = 0;
		/* note this loop doesn't get executed if lb==1 */
		for (i = lb - 2; i >= 0; i--)
			if (b[i] == '\\') {
				if (escaped)
					escaped = 0;
				else
					escaped = 1;
			} else
				break;
		if (!escaped)
			lb--;
	}

	/* lb == 0 means 'b' is the root domain, so 'a' must be in 'b'. */
	if (lb == 0U)
		return (1);

	/* 'b' longer than 'a' means 'a' can't be in 'b'. */
	if (lb > la)
		return (0);

	/* 'a' and 'b' being equal at this point indicates sameness. */
	if (lb == la)
		return (strncasecmp(a, b, lb) == 0);

	/* Ok, we know la > lb. */

	diff = la - lb;

	/*
	 * If 'a' is only 1 character longer than 'b', then it can't be
	 * a subdomain of 'b' (because of the need for the '.' label
	 * separator).
	 */
	if (diff < 2)
		return (0);

	/*
	 * If the character before the last 'lb' characters of 'b'
	 * isn't '.', then it can't be a match (this lets us avoid
	 * having "foobar.com" match "bar.com").
	 */
	if (a[diff - 1] != '.')
		return (0);

	/*
	 * We're not sure about that '.', however.  It could be escaped
         * and thus not a really a label separator.
	 */
	escaped = 0;
	for (i = diff - 2; i >= 0; i--)
		if (a[i] == '\\') {
			if (escaped)
				escaped = 0;
			else
				escaped = 1;
		} else
			break;
	if (escaped)
		return (0);
	  
	/* Now compare aligned trailing substring. */
	cp = a + diff;
	return (strncasecmp(cp, b, lb) == 0);
}