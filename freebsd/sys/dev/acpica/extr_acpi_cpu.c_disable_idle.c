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
struct acpi_cpu_softc {int /*<<< orphan*/  cpu_disable_idle; TYPE_1__* cpu_pcpu; } ;
typedef  int /*<<< orphan*/  cpuset_t ;
struct TYPE_2__ {int /*<<< orphan*/  pc_cpuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SETOF (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  smp_no_rendezvous_barrier ; 
 int /*<<< orphan*/  smp_rendezvous_cpus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
disable_idle(struct acpi_cpu_softc *sc)
{
    cpuset_t cpuset;

    CPU_SETOF(sc->cpu_pcpu->pc_cpuid, &cpuset);
    sc->cpu_disable_idle = TRUE;

    /*
     * Ensure that the CPU is not in idle state or in acpi_cpu_idle().
     * Note that this code depends on the fact that the rendezvous IPI
     * can not penetrate context where interrupts are disabled and acpi_cpu_idle
     * is called and executed in such a context with interrupts being re-enabled
     * right before return.
     */
    smp_rendezvous_cpus(cpuset, smp_no_rendezvous_barrier, NULL,
	smp_no_rendezvous_barrier, NULL);
}