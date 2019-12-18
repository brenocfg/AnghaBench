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
 int /*<<< orphan*/  CVMX_CIU_MBOX_CLRX (int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 
 unsigned int hard_int_mask (int) ; 
 int /*<<< orphan*/  mips_wbflush () ; 
 int /*<<< orphan*/  mips_wr_ebase (int) ; 
 int /*<<< orphan*/  octeon_ciu_reset () ; 
 int platform_ipi_hardintr_num () ; 
 int /*<<< orphan*/  set_intr_mask (unsigned int) ; 

void
platform_init_ap(int cpuid)
{
	unsigned ciu_int_mask, clock_int_mask, ipi_int_mask;

	/*
	 * Set the exception base.
	 */
	mips_wr_ebase(0x80000000);

	/*
	 * Clear any pending IPIs.
	 */
	cvmx_write_csr(CVMX_CIU_MBOX_CLRX(cpuid), 0xffffffff);

	/*
	 * Set up interrupts.
	 */
	octeon_ciu_reset();

	/*
	 * Unmask the clock, ipi and ciu interrupts.
	 */
	ciu_int_mask = hard_int_mask(0);
	clock_int_mask = hard_int_mask(5);
	ipi_int_mask = hard_int_mask(platform_ipi_hardintr_num());
	set_intr_mask(ciu_int_mask | clock_int_mask | ipi_int_mask);

	mips_wbflush();
}