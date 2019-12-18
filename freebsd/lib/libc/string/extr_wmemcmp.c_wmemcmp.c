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
typedef  scalar_t__ wchar_t ;

/* Variables and functions */

int
wmemcmp(const wchar_t *s1, const wchar_t *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++) {
		if (*s1 != *s2) {
			/* wchar might be unsigned */
			return *s1 > *s2 ? 1 : -1; 
		}
		s1++;
		s2++;
	}
	return 0;
}