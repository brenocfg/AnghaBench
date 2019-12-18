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

/* Variables and functions */
 int _bcs_toupper (int /*<<< orphan*/ ) ; 

int
_citrus_bcs_strcasecmp(const char * __restrict str1,
    const char * __restrict str2)
{
	int c1, c2;

	c1 = c2 = 1;

	while (c1 && c2 && c1 == c2) {
		c1 = _bcs_toupper(*str1++);
		c2 = _bcs_toupper(*str2++);
	}

	return ((c1 == c2) ? 0 : ((c1 > c2) ? 1 : -1));
}