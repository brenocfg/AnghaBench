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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  scalar_t__ bus_space_handle_t ;
typedef  scalar_t__ bus_size_t ;

/* Variables and functions */

void
bus_space_write_multi_4(bus_space_tag_t t, bus_space_handle_t h,
    bus_size_t offset, uint32_t *datap, bus_size_t count)
{
	h += offset;

	while (count--) {
		*((volatile uint32_t *)h) = *datap++;
	}
}