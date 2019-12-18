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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MV_MISC_BASE ; 
 int /*<<< orphan*/  SAMPLE_AT_RESET_HI ; 
 int /*<<< orphan*/  SAMPLE_AT_RESET_LO ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 

__attribute__((used)) static uint64_t
get_sar_value_armadaxp(void)
{
	uint32_t sar_low, sar_high;

	sar_high = bus_space_read_4(fdtbus_bs_tag, MV_MISC_BASE,
	    SAMPLE_AT_RESET_HI);
	sar_low = bus_space_read_4(fdtbus_bs_tag, MV_MISC_BASE,
	    SAMPLE_AT_RESET_LO);
	return (((uint64_t)sar_high << 32) | sar_low);
}