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

__attribute__((used)) static wchar_t * wcscpy(wchar_t *s1, const wchar_t *s2)
{
	wchar_t *dest = s1;
	while ((*s1 = *s2) != L'\0')
		++s1, ++s2;
	return dest;
}