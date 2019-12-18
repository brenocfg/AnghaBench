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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/ * psci_fnids; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSCI_FNID_CPU_ON ; 
 size_t PSCI_FN_CPU_ON ; 
 int psci_call (int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long) ; 
 TYPE_1__* psci_softc ; 

int
psci_cpu_on(unsigned long cpu, unsigned long entry, unsigned long context_id)
{
	uint32_t fnid;

	fnid = PSCI_FNID_CPU_ON;
	if (psci_softc != NULL)
		fnid = psci_softc->psci_fnids[PSCI_FN_CPU_ON];

	/* PSCI v0.1 and v0.2 both support cpu_on. */
	return (psci_call(fnid, cpu, entry, context_id));
}