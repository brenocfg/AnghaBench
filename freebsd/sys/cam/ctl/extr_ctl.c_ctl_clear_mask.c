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
typedef  int uint32_t ;

/* Variables and functions */

int
ctl_clear_mask(uint32_t *mask, uint32_t bit)
{
	uint32_t chunk, piece;

	chunk = bit >> 5;
	piece = bit % (sizeof(uint32_t) * 8);

	if ((mask[chunk] & (1 << piece)) == 0)
		return (-1);
	else
		mask[chunk] &= ~(1 << piece);

	return (0);
}