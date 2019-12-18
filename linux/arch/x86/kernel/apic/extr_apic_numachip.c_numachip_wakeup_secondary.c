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
 unsigned long APIC_DM_INIT ; 
 unsigned long APIC_DM_STARTUP ; 
 int /*<<< orphan*/  numachip_apic_icr_write (int,unsigned long) ; 

__attribute__((used)) static int numachip_wakeup_secondary(int phys_apicid, unsigned long start_rip)
{
	numachip_apic_icr_write(phys_apicid, APIC_DM_INIT);
	numachip_apic_icr_write(phys_apicid, APIC_DM_STARTUP |
		(start_rip >> 12));

	return 0;
}