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
 int APIC_DM_FIXED ; 
 int /*<<< orphan*/  APIC_LVTCMCI ; 
 int THRESHOLD_APIC_VECTOR ; 
 int /*<<< orphan*/  apic_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmci_discover (int) ; 
 int /*<<< orphan*/  cmci_recheck () ; 
 int /*<<< orphan*/  cmci_supported (int*) ; 
 int /*<<< orphan*/  intel_threshold_interrupt ; 
 int /*<<< orphan*/  mce_threshold_vector ; 

__attribute__((used)) static void intel_init_cmci(void)
{
	int banks;

	if (!cmci_supported(&banks))
		return;

	mce_threshold_vector = intel_threshold_interrupt;
	cmci_discover(banks);
	/*
	 * For CPU #0 this runs with still disabled APIC, but that's
	 * ok because only the vector is set up. We still do another
	 * check for the banks later for CPU #0 just to make sure
	 * to not miss any events.
	 */
	apic_write(APIC_LVTCMCI, THRESHOLD_APIC_VECTOR|APIC_DM_FIXED);
	cmci_recheck();
}