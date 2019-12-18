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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */

wchar_t *
wcsncpy(wchar_t * __restrict dst, const wchar_t * __restrict src, size_t n)
{
	if (n != 0) {
		wchar_t *d = dst;
		const wchar_t *s = src;

		do {
			if ((*d++ = *s++) == L'\0') {
				/* NUL pad the remaining n-1 bytes */
				while (--n != 0)
					*d++ = L'\0';
				break;
			}
		} while (--n != 0);
	}
	return (dst);
}