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
 int /*<<< orphan*/ * apic ; 
 int /*<<< orphan*/  apic_x2apic_phys ; 
 scalar_t__ x2apic_fadt_phys () ; 
 scalar_t__ x2apic_mode ; 
 scalar_t__ x2apic_phys ; 

__attribute__((used)) static int x2apic_phys_probe(void)
{
	if (x2apic_mode && (x2apic_phys || x2apic_fadt_phys()))
		return 1;

	return apic == &apic_x2apic_phys;
}