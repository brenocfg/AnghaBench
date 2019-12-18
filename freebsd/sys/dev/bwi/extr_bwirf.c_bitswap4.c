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
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static __inline uint16_t
bitswap4(uint16_t val)
{
	uint16_t ret;

	ret = (val & 0x8) >> 3;
	ret |= (val & 0x4) >> 1;
	ret |= (val & 0x2) << 1;
	ret |= (val & 0x1) << 3;
	return ret;
}