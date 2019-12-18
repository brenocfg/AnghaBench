#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct TYPE_2__ {void* cf_sleep; } ;

/* Variables and functions */
#define  AML_SOC_HW_REV_M3 128 
 scalar_t__ aml8726_aobus_kva_base ; 
 int /*<<< orphan*/  aml8726_fixup_busfreq () ; 
 int /*<<< orphan*/  aml8726_identify_soc () ; 
 int aml8726_soc_hw_rev ; 
 scalar_t__ cpufunc_nullop ; 
 TYPE_1__ cpufuncs ; 
 scalar_t__ devmap_ptov (int,int) ; 

void
platform_gpio_init(void)
{

	/*
	 * The UART console driver used for debugging early boot code
	 * needs to know the virtual base address of the aobus.  It's
	 * expected to equal SOCDEV_VA prior to initarm calling setttb
	 * ... afterwards it needs to be updated due to the new page
	 * tables.
	 *
	 * This means there's a deadzone in initarm between setttb
	 * and platform_gpio_init during which printf can't be used.
	 */
	aml8726_aobus_kva_base =
	    (vm_offset_t)devmap_ptov(0xc8100000, 0x100000);

	/*
	 * The hardware mux used by clkmsr is unique to the SoC (though
	 * currently clk81 is at a fixed location, however that might
	 * change in the future).
	 */
	aml8726_identify_soc();

	/*
	 * My aml8726-m3 development box which identifies the CPU as
	 * a Cortex A9-r2 rev 4 randomly locks up during boot when WFI
	 * is used.
	 */
	switch (aml8726_soc_hw_rev) {
	case AML_SOC_HW_REV_M3:
		cpufuncs.cf_sleep = (void *)cpufunc_nullop;
		break;
	default:
		break;
	}

	/*
	 * This FDT fixup should arguably be called through fdt_fixup_table,
	 * however currently there's no mechanism to specify a fixup which
	 * should always be invoked.
	 *
	 * It needs to be called prior to the console being initialized which
	 * is why it's called here, rather than from platform_late_init.
	 */
	aml8726_fixup_busfreq();
}