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
typedef  scalar_t__ const wchar_t ;

/* Variables and functions */

wchar_t	*
wmemchr(const wchar_t *s, wchar_t c, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++) {
		if (*s == c) {
			/* LINTED const castaway */
			return (wchar_t *)s;
		}
		s++;
	}
	return NULL;
}