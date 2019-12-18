#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct acpi_softc {int dummy; } ;
struct TYPE_5__ {TYPE_1__* mr_op; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* reinit ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiSetFirmwareWakingVector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPU_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_wakeup_cpus (struct acpi_softc*) ; 
 int /*<<< orphan*/  initializecpu () ; 
 int /*<<< orphan*/  intr_resume (int) ; 
 int /*<<< orphan*/  lapic_xapic_mode () ; 
 int /*<<< orphan*/  mca_resume () ; 
 TYPE_2__ mem_range_softc ; 
 int /*<<< orphan*/  pmap_init_pat () ; 
 int /*<<< orphan*/  resume_cpus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  suspcpus ; 
 int /*<<< orphan*/  switchticks ; 
 int /*<<< orphan*/  switchtime ; 
 int /*<<< orphan*/  ticks ; 
 int /*<<< orphan*/  ucode_reload () ; 
 int /*<<< orphan*/  vmm_resume_p () ; 

int
acpi_wakeup_machdep(struct acpi_softc *sc, int state, int sleep_result,
    int intr_enabled)
{

	if (sleep_result == -1)
		return (sleep_result);

	if (!intr_enabled) {
		/* Wakeup MD procedures in interrupt disabled context */
		if (sleep_result == 1) {
			ucode_reload();
			pmap_init_pat();
			initializecpu();
			PCPU_SET(switchtime, 0);
			PCPU_SET(switchticks, ticks);
#ifdef DEV_APIC
			lapic_xapic_mode();
#endif
#ifdef SMP
			if (!CPU_EMPTY(&suspcpus))
				acpi_wakeup_cpus(sc);
#endif
		}

#ifdef SMP
		if (!CPU_EMPTY(&suspcpus))
			resume_cpus(suspcpus);
#endif
		mca_resume();
#ifdef __amd64__
		if (vmm_resume_p != NULL)
			vmm_resume_p();
#endif
		intr_resume(/*suspend_cancelled*/false);

		AcpiSetFirmwareWakingVector(0, 0);
	} else {
		/* Wakeup MD procedures in interrupt enabled context */
		if (sleep_result == 1 && mem_range_softc.mr_op != NULL &&
		    mem_range_softc.mr_op->reinit != NULL)
			mem_range_softc.mr_op->reinit(&mem_range_softc);
	}

	return (sleep_result);
}