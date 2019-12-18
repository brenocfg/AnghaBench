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
 unsigned char* charmap ; 

int
ascii_strncasecmp(const char *s1, const char *s2, register size_t n)
{
	register const unsigned char *cm = charmap,
			*us1 = (const unsigned char *)s1,
			*us2 = (const unsigned char *)s2;

	for (;;) {
		if (n == 0) {
			/*
			 * We've run out of characters that we should
			 * compare, and they've all been equal; return
			 * 0, to indicate that the prefixes are the
			 * same.
			 */
			return(0);
		}
		if (cm[*us1] != cm[*us2++]) {
			/*
			 * We've found a mismatch.
			 */
			break;
		}
		if (*us1++ == '\0') {
			/*
			 * We've run out of characters *to* compare,
			 * and they've all been equal; return 0, to
			 * indicate that the strings are the same.
			 */
			return(0);
		}
		n--;
	}
	return(cm[*us1] - cm[*--us2]);
}