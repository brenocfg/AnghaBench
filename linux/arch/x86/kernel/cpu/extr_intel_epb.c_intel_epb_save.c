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
typedef  int u64 ;

/* Variables and functions */
 int EPB_MASK ; 
 int EPB_SAVED ; 
 int /*<<< orphan*/  MSR_IA32_ENERGY_PERF_BIAS ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saved_epb ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int intel_epb_save(void)
{
	u64 epb;

	rdmsrl(MSR_IA32_ENERGY_PERF_BIAS, epb);
	/*
	 * Ensure that saved_epb will always be nonzero after this write even if
	 * the EPB value read from the MSR is 0.
	 */
	this_cpu_write(saved_epb, (epb & EPB_MASK) | EPB_SAVED);

	return 0;
}