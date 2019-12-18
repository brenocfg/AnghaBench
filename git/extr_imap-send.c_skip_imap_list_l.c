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
 scalar_t__ isspace (unsigned char) ; 

__attribute__((used)) static int skip_imap_list_l(char **sp, int level)
{
	char *s = *sp;

	for (;;) {
		while (isspace((unsigned char)*s))
			s++;
		if (level && *s == ')') {
			s++;
			break;
		}
		if (*s == '(') {
			/* sublist */
			s++;
			if (skip_imap_list_l(&s, level + 1))
				goto bail;
		} else if (*s == '"') {
			/* quoted string */
			s++;
			for (; *s != '"'; s++)
				if (!*s)
					goto bail;
			s++;
		} else {
			/* atom */
			for (; *s && !isspace((unsigned char)*s); s++)
				if (level && *s == ')')
					break;
		}

		if (!level)
			break;
		if (!*s)
			goto bail;
	}
	*sp = s;
	return 0;

bail:
	return -1;
}