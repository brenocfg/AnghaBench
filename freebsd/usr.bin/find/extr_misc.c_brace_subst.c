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
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* reallocf (char*,size_t) ; 
 int strlen (char*) ; 
 char* strstr (char const*,char*) ; 

void
brace_subst(char *orig, char **store, char *path, size_t len)
{
	const char *pastorigend, *p, *q;
	char *dst;
	size_t newlen, plen;

	plen = strlen(path);
	newlen = strlen(orig) + 1;
	pastorigend = orig + newlen;
	for (p = orig; (q = strstr(p, "{}")) != NULL; p = q + 2) {
		if (plen > 2 && newlen + plen - 2 < newlen)
			errx(2, "brace_subst overflow");
		newlen += plen - 2;
	}
	if (newlen > len) {
		*store = reallocf(*store, newlen);
		if (*store == NULL)
			err(2, NULL);
	}
	dst = *store;
	for (p = orig; (q = strstr(p, "{}")) != NULL; p = q + 2) {
		memcpy(dst, p, q - p);
		dst += q - p;
		memcpy(dst, path, plen);
		dst += plen;
	}
	memcpy(dst, p, pastorigend - p);
}