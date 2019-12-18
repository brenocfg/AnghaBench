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
typedef  scalar_t__ usb_size_t ;
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t
usb_intr_find_best_slot(usb_size_t *ptr, uint8_t start,
    uint8_t end, uint8_t mask)
{
	usb_size_t min = (usb_size_t)-1;
	usb_size_t sum;
	uint8_t x;
	uint8_t y;
	uint8_t z;

	y = 0;

	/* find the last slot with lesser used bandwidth */

	for (x = start; x < end; x++) {

		sum = 0;

		/* compute sum of bandwidth */
		for (z = x; z < end; z++) {
			if (mask & (1U << (z - x)))
				sum += ptr[z];
		}

		/* check if the current multi-slot is more optimal */
		if (min >= sum) {
			min = sum;
			y = x;
		}

		/* check if the mask is about to be shifted out */
		if (mask & (1U << (end - 1 - x)))
			break;
	}
	return (y);
}