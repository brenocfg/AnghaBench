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

wchar_t *
wcpncpy(wchar_t * __restrict dst, const wchar_t * __restrict src, size_t n)
{

	for (; n--; dst++, src++) {
		if (!(*dst = *src)) {
			wchar_t *ret = dst;
			while (n--)
				*++dst = L'\0';
			return (ret);
		}
	}
	return (dst);
}