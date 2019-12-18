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
 int hard_int_mask (int) ; 
 int /*<<< orphan*/  mips_wbflush () ; 
 int /*<<< orphan*/  platform_ipi_clear () ; 
 int /*<<< orphan*/  platform_ipi_softintr_num () ; 
 int /*<<< orphan*/  set_intr_mask (int) ; 
 int soft_int_mask (int /*<<< orphan*/ ) ; 

void
platform_init_ap(int cpuid)
{
	uint32_t clock_int_mask;
	uint32_t ipi_intr_mask;

	/*
	 * Clear any pending IPIs.
	 */
	platform_ipi_clear();

	/*
	 * Unmask the clock and ipi interrupts.
	 */
	ipi_intr_mask = soft_int_mask(platform_ipi_softintr_num());
	clock_int_mask = hard_int_mask(5);
	set_intr_mask(ipi_intr_mask | clock_int_mask);

	mips_wbflush();
}