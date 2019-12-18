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
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ ,int,char*,int) ; 
 int CPUID_ACPI ; 
 int CPUID_TM ; 
 int cpu_feature ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
p4tcc_identify(driver_t *driver, device_t parent)
{

	if ((cpu_feature & (CPUID_ACPI | CPUID_TM)) != (CPUID_ACPI | CPUID_TM))
		return;

	/* Make sure we're not being doubly invoked. */
	if (device_find_child(parent, "p4tcc", -1) != NULL)
		return;

	/*
	 * We attach a p4tcc child for every CPU since settings need to
	 * be performed on every CPU in the SMP case.  See section 13.15.3
	 * of the IA32 Intel Architecture Software Developer's Manual,
	 * Volume 3, for more info.
	 */
	if (BUS_ADD_CHILD(parent, 10, "p4tcc", -1) == NULL)
		device_printf(parent, "add p4tcc child failed\n");
}