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
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ lapic_paddr ; 

__attribute__((used)) static void
apic_identify(driver_t *driver, device_t parent)
{

	/*
	 * Add at order 12.  acpi0 is probed at order 10 and legacy0
	 * is probed at order 11.
	 */
	if (lapic_paddr != 0)
		BUS_ADD_CHILD(parent, 12, "apic", 0);
}