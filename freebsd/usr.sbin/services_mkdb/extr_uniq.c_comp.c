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
 int /*<<< orphan*/  err (int,char*,size_t) ; 
 int isalnum (unsigned char const) ; 
 scalar_t__ isspace (unsigned char const) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char const*,size_t) ; 

__attribute__((used)) static int
comp(const char *origline, char **compline, size_t *len)
{
	const unsigned char *p;
	unsigned char *q;
	char *cline;
	size_t l = *len, complen;
	int hasalnum, iscomment;

	/* Eat leading space */
	for (p = (const unsigned char *)origline; l && *p && isspace(*p);
	    p++, l--)
		continue;
	if ((cline = malloc(l + 1)) == NULL)
		err(1, "Cannot allocate %zu bytes", l + 1);
	(void)memcpy(cline, p, l);
	cline[l] = '\0';
	if (*cline == '\0')
		return 0;

	complen = 0;
	hasalnum = 0;
	iscomment = 0;

	for (q = (unsigned char *)cline; l && *p; p++, l--) {
		if (isspace(*p)) {
			if (complen && isspace(q[-1]))
				continue;
			*q++ = ' ';
			complen++;
		} else {
			if (!iscomment && *p == '#') {
				if (hasalnum)
					break;
				iscomment = 1;
			} else
				hasalnum |= isalnum(*p);
			*q++ = *p;
			complen++;
		}
	}

	/* Eat trailing space */
	while (complen && isspace(q[-1])) {
		--q;
		--complen;
	}
	*q = '\0';
	*compline = cline;
	*len = complen;
	return hasalnum;
}