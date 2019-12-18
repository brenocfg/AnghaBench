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

size_t
wcsspn(const wchar_t *s, const wchar_t *set)
{
	const wchar_t *p;
	const wchar_t *q;

	p = s;
	while (*p) {
		q = set;
		while (*q) {
			if (*p == *q)
				break;
			q++;
		}
		if (!*q)
			goto done;
		p++;
	}

done:
	return (p - s);
}