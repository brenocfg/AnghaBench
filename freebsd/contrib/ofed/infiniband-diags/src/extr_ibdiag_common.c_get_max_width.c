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

__attribute__((used)) static unsigned int get_max_width(unsigned int num)
{
	unsigned r = 0;			/* 1x */

	if (num & 8)
		r = 3;			/* 12x */
	else {
		if (num & 4)
			r = 2;		/* 8x */
		else if (num & 2)
			r = 1;		/* 4x */
		else if (num & 0x10)
			r = 4;		/* 2x */
	}

        return (1 << r);
}