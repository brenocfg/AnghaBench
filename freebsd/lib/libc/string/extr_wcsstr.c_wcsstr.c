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
typedef  int wchar_t ;

/* Variables and functions */
 size_t wcslen (int const*) ; 
 scalar_t__ wcsncmp (int const*,int const*,size_t) ; 

wchar_t *
wcsstr(const wchar_t * __restrict s, const wchar_t * __restrict find)
{
	wchar_t c, sc;
	size_t len;

	if ((c = *find++) != L'\0') {
		len = wcslen(find);
		do {
			do {
				if ((sc = *s++) == L'\0')
					return (NULL);
			} while (sc != c);
		} while (wcsncmp(s, find, len) != 0);
		s--;
	}
	return ((wchar_t *)s);
}