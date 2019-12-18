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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  beripic_setup_ipi (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/  devclass_get_device (int /*<<< orphan*/ ,int) ; 
 int mips_rd_status () ; 
 int /*<<< orphan*/  mips_wr_status (int) ; 
 int /*<<< orphan*/ * picmap ; 
 int platform_ipi_hardintr_num () ; 

void
platform_init_secondary(int cpuid)
{
	device_t ic;
	int ipi;

	ipi = platform_ipi_hardintr_num();

	ic = devclass_get_device(devclass_find("beripic"), cpuid);
	picmap[cpuid] = ic;
	beripic_setup_ipi(ic, cpuid, ipi);

	/* Unmask the interrupt */
	if (cpuid != 0) {
		mips_wr_status(mips_rd_status() | (((1 << ipi) << 8) << 2));
	}
}