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
wcscat(wchar_t * __restrict s1, const wchar_t * __restrict s2)
{
	wchar_t *cp;

	cp = s1;
	while (*cp != L'\0')
		cp++;
	while ((*cp++ = *s2++) != L'\0')
		;

	return (s1);
}