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

__attribute__((used)) static uint32_t
calc_hi20_imm(uint32_t value)
{
	/*
	 * There is the arithmetical hack that can remove conditional
	 * statement. But I implement it in straightforward way.
	 */
	if ((value & 0x800) != 0)
		value += 0x1000;
	return (value & ~0xfff);
}