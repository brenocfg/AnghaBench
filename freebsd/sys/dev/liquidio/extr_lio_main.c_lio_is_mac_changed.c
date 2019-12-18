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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

__attribute__((used)) static int
lio_is_mac_changed(uint8_t *new, uint8_t *old)
{

	return ((new[0] != old[0]) || (new[1] != old[1]) ||
		(new[2] != old[2]) || (new[3] != old[3]) ||
		(new[4] != old[4]) || (new[5] != old[5]));
}