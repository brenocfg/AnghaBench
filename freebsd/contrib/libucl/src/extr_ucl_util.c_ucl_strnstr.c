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
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

char *
ucl_strnstr (const char *s, const char *find, int len)
{
	char c, sc;
	int mlen;

	if ((c = *find++) != 0) {
		mlen = strlen (find);
		do {
			do {
				if ((sc = *s++) == 0 || len-- == 0)
					return (NULL);
			} while (sc != c);
		} while (strncmp (s, find, mlen) != 0);
		s--;
	}
	return ((char *)s);
}