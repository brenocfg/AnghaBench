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
 int /*<<< orphan*/  mxc_iomux_release_pin (unsigned int const) ; 

void mxc_iomux_release_multiple_pins(const unsigned int *pin_list, int count)
{
	const unsigned int *p = pin_list;
	int i;

	for (i = 0; i < count; i++) {
		mxc_iomux_release_pin(*p);
		p++;
	}
}