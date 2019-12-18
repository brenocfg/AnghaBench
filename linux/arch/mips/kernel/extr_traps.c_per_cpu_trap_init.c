#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ asid_cache; } ;
struct TYPE_4__ {int /*<<< orphan*/  mm; int /*<<< orphan*/ * active_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ CAUSEB_IP ; 
 scalar_t__ CAUSEB_TI ; 
 int CP0_LEGACY_COMPARE_IRQ ; 
 scalar_t__ CP0_LEGACY_PERFCNT_IRQ ; 
 int INTCTLB_IPFDC ; 
 int INTCTLB_IPPCI ; 
 int INTCTLB_IPTI ; 
 int /*<<< orphan*/  TLBMISS_HANDLER_SETUP () ; 
 scalar_t__ asid_first_version (unsigned int) ; 
 int /*<<< orphan*/  configure_exception_vector () ; 
 int /*<<< orphan*/  configure_hwrena () ; 
 int /*<<< orphan*/  configure_status () ; 
 int cp0_compare_irq ; 
 scalar_t__ cp0_compare_irq_shift ; 
 int cp0_fdc_irq ; 
 int cp0_perfcount_irq ; 
 int /*<<< orphan*/  cpu_cache_init () ; 
 TYPE_3__* cpu_data ; 
 scalar_t__ cpu_has_mips_r2_r6 ; 
 scalar_t__ cpu_has_mmid ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  enter_lazy_tlb (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/  mmgrab (int /*<<< orphan*/ *) ; 
 int read_c0_intctl () ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  tlb_init () ; 

void per_cpu_trap_init(bool is_boot_cpu)
{
	unsigned int cpu = smp_processor_id();

	configure_status();
	configure_hwrena();

	configure_exception_vector();

	/*
	 * Before R2 both interrupt numbers were fixed to 7, so on R2 only:
	 *
	 *  o read IntCtl.IPTI to determine the timer interrupt
	 *  o read IntCtl.IPPCI to determine the performance counter interrupt
	 *  o read IntCtl.IPFDC to determine the fast debug channel interrupt
	 */
	if (cpu_has_mips_r2_r6) {
		cp0_compare_irq_shift = CAUSEB_TI - CAUSEB_IP;
		cp0_compare_irq = (read_c0_intctl() >> INTCTLB_IPTI) & 7;
		cp0_perfcount_irq = (read_c0_intctl() >> INTCTLB_IPPCI) & 7;
		cp0_fdc_irq = (read_c0_intctl() >> INTCTLB_IPFDC) & 7;
		if (!cp0_fdc_irq)
			cp0_fdc_irq = -1;

	} else {
		cp0_compare_irq = CP0_LEGACY_COMPARE_IRQ;
		cp0_compare_irq_shift = CP0_LEGACY_PERFCNT_IRQ;
		cp0_perfcount_irq = -1;
		cp0_fdc_irq = -1;
	}

	if (cpu_has_mmid)
		cpu_data[cpu].asid_cache = 0;
	else if (!cpu_data[cpu].asid_cache)
		cpu_data[cpu].asid_cache = asid_first_version(cpu);

	mmgrab(&init_mm);
	current->active_mm = &init_mm;
	BUG_ON(current->mm);
	enter_lazy_tlb(&init_mm, current);

	/* Boot CPU's cache setup in setup_arch(). */
	if (!is_boot_cpu)
		cpu_cache_init();
	tlb_init();
	TLBMISS_HANDLER_SETUP();
}