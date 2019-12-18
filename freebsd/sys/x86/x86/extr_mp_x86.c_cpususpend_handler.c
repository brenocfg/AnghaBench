#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_4__ {int /*<<< orphan*/  (* cpu_resume ) () ;} ;
struct TYPE_3__ {int /*<<< orphan*/  sp_fpususpend; int /*<<< orphan*/  sp_pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR_ATOMIC (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ISSET (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET_ATOMIC (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 size_t PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ cpu_ops ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  fpuresume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpususpend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia32_pause () ; 
 int /*<<< orphan*/  initializecpu () ; 
 int /*<<< orphan*/  invltlb_glob () ; 
 int /*<<< orphan*/  lapic_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_xapic_mode () ; 
 int /*<<< orphan*/  mca_resume () ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  npxresume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  npxsuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_init_pat () ; 
 int /*<<< orphan*/  resuming_cpus ; 
 scalar_t__ savectx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_ipi_mtx ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  suspended_cpus ; 
 TYPE_1__** susppcbs ; 
 int /*<<< orphan*/  switchticks ; 
 int /*<<< orphan*/  switchtime ; 
 int /*<<< orphan*/  ticks ; 
 int /*<<< orphan*/  toresume_cpus ; 
 int /*<<< orphan*/  ucode_reload () ; 
 int /*<<< orphan*/  vmm_resume_p () ; 
 int /*<<< orphan*/  wbinvd () ; 

void
cpususpend_handler(void)
{
	u_int cpu;

	mtx_assert(&smp_ipi_mtx, MA_NOTOWNED);

	cpu = PCPU_GET(cpuid);
	if (savectx(&susppcbs[cpu]->sp_pcb)) {
#ifdef __amd64__
		fpususpend(susppcbs[cpu]->sp_fpususpend);
#else
		npxsuspend(susppcbs[cpu]->sp_fpususpend);
#endif
		/*
		 * suspended_cpus is cleared shortly after each AP is restarted
		 * by a Startup IPI, so that the BSP can proceed to restarting
		 * the next AP.
		 *
		 * resuming_cpus gets cleared when the AP completes
		 * initialization after having been released by the BSP.
		 * resuming_cpus is probably not the best name for the
		 * variable, because it is actually a set of processors that
		 * haven't resumed yet and haven't necessarily started resuming.
		 *
		 * Note that suspended_cpus is meaningful only for ACPI suspend
		 * as it's not really used for Xen suspend since the APs are
		 * automatically restored to the running state and the correct
		 * context.  For the same reason resumectx is never called in
		 * that case.
		 */
		CPU_SET_ATOMIC(cpu, &suspended_cpus);
		CPU_SET_ATOMIC(cpu, &resuming_cpus);

		/*
		 * Invalidate the cache after setting the global status bits.
		 * The last AP to set its bit may end up being an Owner of the
		 * corresponding cache line in MOESI protocol.  The AP may be
		 * stopped before the cache line is written to the main memory.
		 */
		wbinvd();
	} else {
#ifdef __amd64__
		fpuresume(susppcbs[cpu]->sp_fpususpend);
#else
		npxresume(susppcbs[cpu]->sp_fpususpend);
#endif
		pmap_init_pat();
		initializecpu();
		PCPU_SET(switchtime, 0);
		PCPU_SET(switchticks, ticks);

		/* Indicate that we have restarted and restored the context. */
		CPU_CLR_ATOMIC(cpu, &suspended_cpus);
	}

	/* Wait for resume directive */
	while (!CPU_ISSET(cpu, &toresume_cpus))
		ia32_pause();

	/* Re-apply microcode updates. */
	ucode_reload();

#ifdef __i386__
	/* Finish removing the identity mapping of low memory for this AP. */
	invltlb_glob();
#endif

	if (cpu_ops.cpu_resume)
		cpu_ops.cpu_resume();
#ifdef __amd64__
	if (vmm_resume_p)
		vmm_resume_p();
#endif

	/* Resume MCA and local APIC */
	lapic_xapic_mode();
	mca_resume();
	lapic_setup(0);

	/* Indicate that we are resumed */
	CPU_CLR_ATOMIC(cpu, &resuming_cpus);
	CPU_CLR_ATOMIC(cpu, &suspended_cpus);
	CPU_CLR_ATOMIC(cpu, &toresume_cpus);
}