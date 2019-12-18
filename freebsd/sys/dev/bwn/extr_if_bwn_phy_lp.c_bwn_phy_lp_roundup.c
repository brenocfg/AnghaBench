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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t
bwn_phy_lp_roundup(uint32_t value, uint32_t div, uint8_t pre)
{
	uint32_t i, q, r;

	if (div == 0)
		return (0);

	for (i = 0, q = value / div, r = value % div; i < pre; i++) {
		q <<= 1;
		if (r << 1 >= div) {
			q++;
			r = (r << 1) - div;
		}
	}
	if (r << 1 >= div)
		q++;
	return (q);
}