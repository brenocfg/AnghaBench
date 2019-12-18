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
 unsigned int ACPI_MADT_ENABLED ; 
 scalar_t__ MAXCPU ; 
 unsigned int MAX_APIC_ID ; 
 int /*<<< orphan*/  max (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_apic_id ; 
 scalar_t__ mp_maxid ; 
 scalar_t__ mp_ncpus ; 

__attribute__((used)) static void
madt_parse_cpu(unsigned int apic_id, unsigned int flags)
{

	if (!(flags & ACPI_MADT_ENABLED) ||
#ifdef SMP
	    mp_ncpus == MAXCPU ||
#endif
	    apic_id > MAX_APIC_ID)
		return;

#ifdef SMP
	mp_ncpus++;
	mp_maxid = mp_ncpus - 1;
#endif
	max_apic_id = max(apic_id, max_apic_id);
}