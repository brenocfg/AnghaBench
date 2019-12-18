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
typedef  scalar_t__ suspend_state_t ;

/* Variables and functions */
 scalar_t__ CS5536_PM1_STS ; 
 int EINVAL ; 
 scalar_t__ PM_SUSPEND_MEM ; 
 scalar_t__ acpi_base ; 
 int /*<<< orphan*/  do_olpc_suspend_lowlevel () ; 
 unsigned long inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned long,scalar_t__) ; 

__attribute__((used)) static int xo1_power_state_enter(suspend_state_t pm_state)
{
	unsigned long saved_sci_mask;

	/* Only STR is supported */
	if (pm_state != PM_SUSPEND_MEM)
		return -EINVAL;

	/*
	 * Save SCI mask (this gets lost since PM1_EN is used as a mask for
	 * wakeup events, which is not necessarily the same event set)
	 */
	saved_sci_mask = inl(acpi_base + CS5536_PM1_STS);
	saved_sci_mask &= 0xffff0000;

	/* Save CPU state */
	do_olpc_suspend_lowlevel();

	/* Resume path starts here */

	/* Restore SCI mask (using dword access to CS5536_PM1_EN) */
	outl(saved_sci_mask, acpi_base + CS5536_PM1_STS);

	return 0;
}