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
 int TCLK_200MHZ ; 
 int TCLK_250MHZ ; 
 int TCLK_MASK_ARMADA38X ; 
 int TCLK_SHIFT_ARMADA38X ; 
 scalar_t__ get_sar_value_armada38x () ; 

uint32_t
get_tclk_armada38x(void)
{
	uint32_t sar;

	/*
	 * On Armada38x TCLK can be configured to 250 MHz or 200 MHz.
	 * Current setting is read from Sample At Reset register.
	 */
	sar = (uint32_t)get_sar_value_armada38x();
	sar = (sar & TCLK_MASK_ARMADA38X) >> TCLK_SHIFT_ARMADA38X;
	if (sar == 0)
		return (TCLK_250MHZ);
	else
		return (TCLK_200MHZ);
}