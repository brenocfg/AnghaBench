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

__attribute__((used)) static char *
compile_ccl(char **sp, char *t)
{
	int c, d;
	char *s = *sp;

	*t++ = *s++;
	if (*s == '^')
		*t++ = *s++;
	if (*s == ']')
		*t++ = *s++;
	for (; *s && (*t = *s) != ']'; s++, t++)
		if (*s == '[' && ((d = *(s+1)) == '.' || d == ':' || d == '=')) {
			*++t = *++s, t++, s++;
			for (c = *s; (*t = *s) != ']' || c != d; s++, t++)
				if ((c = *s) == '\0')
					return NULL;
		}
	return (*s == ']') ? *sp = ++s, ++t : NULL;
}