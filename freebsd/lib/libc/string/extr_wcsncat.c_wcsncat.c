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
typedef  char wchar_t ;

/* Variables and functions */

wchar_t *
wcsncat(wchar_t * __restrict s1, const wchar_t * __restrict s2, size_t n)
{
	wchar_t *p;
	wchar_t *q;
	const wchar_t *r;

	p = s1;
	while (*p)
		p++;
	q = p;
	r = s2;
	while (n && *r) {
		*q++ = *r++;
		n--;
	}
	*q = '\0';
	return s1;
}