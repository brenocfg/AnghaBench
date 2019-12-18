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
 int /*<<< orphan*/  htote (int /*<<< orphan*/ ) ; 

wchar_t *
wsncpy(wchar_t *s1, const wchar_t *s2, size_t n)
{
	wchar_t *os1 = s1;

	n++;
	while (--n > 0 && (*s1++ = htote(*s2++)) != 0)
		continue;
	if (n > 0)
		while (--n > 0)
			*s1++ = 0;
	return (os1);
}