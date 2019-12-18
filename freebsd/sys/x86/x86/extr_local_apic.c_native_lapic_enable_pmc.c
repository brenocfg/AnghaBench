#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int32_t ;
struct TYPE_2__ {scalar_t__ lvt_masked; } ;

/* Variables and functions */
 size_t APIC_LVT_PMC ; 
 size_t APIC_VER_MAXLVT ; 
 int /*<<< orphan*/  LAPIC_VERSION ; 
 size_t MAXLVTSHIFT ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/ * lapic_map ; 
 size_t lapic_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_update_pmc (int /*<<< orphan*/ *) ; 
 TYPE_1__* lvts ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  smp_rendezvous (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *),int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ smp_started ; 
 int /*<<< orphan*/  x2apic_mode ; 

__attribute__((used)) static int
native_lapic_enable_pmc(void)
{
#ifdef HWPMC_HOOKS
	u_int32_t maxlvt;

	/* Fail if the local APIC is not present. */
	if (!x2apic_mode && lapic_map == NULL)
		return (0);

	/* Fail if the PMC LVT is not present. */
	maxlvt = (lapic_read32(LAPIC_VERSION) & APIC_VER_MAXLVT) >> MAXLVTSHIFT;
	if (maxlvt < APIC_LVT_PMC)
		return (0);

	lvts[APIC_LVT_PMC].lvt_masked = 0;

#ifdef EARLY_AP_STARTUP
	MPASS(mp_ncpus == 1 || smp_started);
	smp_rendezvous(NULL, lapic_update_pmc, NULL, NULL);
#else
#ifdef SMP
	/*
	 * If hwpmc was loaded at boot time then the APs may not be
	 * started yet.  In that case, don't forward the request to
	 * them as they will program the lvt when they start.
	 */
	if (smp_started)
		smp_rendezvous(NULL, lapic_update_pmc, NULL, NULL);
	else
#endif
		lapic_update_pmc(NULL);
#endif
	return (1);
#else
	return (0);
#endif
}