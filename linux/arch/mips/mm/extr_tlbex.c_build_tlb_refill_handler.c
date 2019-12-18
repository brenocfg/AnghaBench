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
struct TYPE_2__ {int vmbits; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_XPA ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int PGDIR_SHIFT ; 
 int PGD_ORDER ; 
 int /*<<< orphan*/  allocate_kscratch () ; 
 int /*<<< orphan*/  build_loongson3_tlb_refill_handler () ; 
 int /*<<< orphan*/  build_r3000_tlb_load_handler () ; 
 int /*<<< orphan*/  build_r3000_tlb_modify_handler () ; 
 int /*<<< orphan*/  build_r3000_tlb_refill_handler () ; 
 int /*<<< orphan*/  build_r3000_tlb_store_handler () ; 
 int /*<<< orphan*/  build_r4000_tlb_load_handler () ; 
 int /*<<< orphan*/  build_r4000_tlb_modify_handler () ; 
 int /*<<< orphan*/  build_r4000_tlb_refill_handler () ; 
 int /*<<< orphan*/  build_r4000_tlb_store_handler () ; 
 int /*<<< orphan*/  build_setup_pgd () ; 
 int check_for_high_segbits ; 
 int /*<<< orphan*/  check_pabits () ; 
 int /*<<< orphan*/  config_htw_params () ; 
 int /*<<< orphan*/  config_xpa_params () ; 
 scalar_t__ cpu_has_3kex ; 
 scalar_t__ cpu_has_htw ; 
 scalar_t__ cpu_has_ldpte ; 
 int /*<<< orphan*/  cpu_has_rixi ; 
 scalar_t__ cpu_has_xpa ; 
 TYPE_1__ current_cpu_data ; 
 int /*<<< orphan*/  flush_tlb_handlers () ; 
 int /*<<< orphan*/  output_pgtable_bits_defines () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  scratch_reg ; 
 int /*<<< orphan*/  setup_pw () ; 

void build_tlb_refill_handler(void)
{
	/*
	 * The refill handler is generated per-CPU, multi-node systems
	 * may have local storage for it. The other handlers are only
	 * needed once.
	 */
	static int run_once = 0;

	if (IS_ENABLED(CONFIG_XPA) && !cpu_has_rixi)
		panic("Kernels supporting XPA currently require CPUs with RIXI");

	output_pgtable_bits_defines();
	check_pabits();

#ifdef CONFIG_64BIT
	check_for_high_segbits = current_cpu_data.vmbits > (PGDIR_SHIFT + PGD_ORDER + PAGE_SHIFT - 3);
#endif

	if (cpu_has_3kex) {
#ifndef CONFIG_MIPS_PGD_C0_CONTEXT
		if (!run_once) {
			build_setup_pgd();
			build_r3000_tlb_refill_handler();
			build_r3000_tlb_load_handler();
			build_r3000_tlb_store_handler();
			build_r3000_tlb_modify_handler();
			flush_tlb_handlers();
			run_once++;
		}
#else
		panic("No R3000 TLB refill handler");
#endif
		return;
	}

	if (cpu_has_ldpte)
		setup_pw();

	if (!run_once) {
		scratch_reg = allocate_kscratch();
		build_setup_pgd();
		build_r4000_tlb_load_handler();
		build_r4000_tlb_store_handler();
		build_r4000_tlb_modify_handler();
		if (cpu_has_ldpte)
			build_loongson3_tlb_refill_handler();
		else
			build_r4000_tlb_refill_handler();
		flush_tlb_handlers();
		run_once++;
	}
	if (cpu_has_xpa)
		config_xpa_params();
	if (cpu_has_htw)
		config_htw_params();
}