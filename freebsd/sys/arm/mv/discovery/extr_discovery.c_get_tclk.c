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
 int /*<<< orphan*/  MV_MPP_BASE ; 
 int /*<<< orphan*/  SAMPLE_AT_RESET_HI ; 
 int TCLK_166MHZ ; 
 int TCLK_200MHZ ; 
 int TCLK_MASK ; 
 int TCLK_SHIFT ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 int /*<<< orphan*/  panic (char*) ; 

uint32_t
get_tclk(void)
{
	uint32_t sar;

	/*
	 * On Discovery TCLK is can be configured to 166 MHz or 200 MHz.
	 * Current setting is read from Sample At Reset register.
	 */
	sar = bus_space_read_4(fdtbus_bs_tag, MV_MPP_BASE, SAMPLE_AT_RESET_HI);
	sar = (sar & TCLK_MASK) >> TCLK_SHIFT;

	switch (sar) {
	case 0:
		return (TCLK_166MHZ);
	case 1:
		return (TCLK_200MHZ);
	default:
		panic("Unknown TCLK settings!");
	}
}