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
typedef  int /*<<< orphan*/  u32 ;
struct work_registers {int /*<<< orphan*/  r3; int /*<<< orphan*/  r2; int /*<<< orphan*/  r1; } ;
struct uasm_reloc {int dummy; } ;
struct uasm_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  C0_BADVADDR ; 
 int /*<<< orphan*/  C0_INDEX ; 
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ PTE_ORDER ; 
 int PTE_T_LOG2 ; 
 int PTRS_PER_PTE ; 
 int /*<<< orphan*/  UASM_i_ADDU (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UASM_i_LW (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UASM_i_MFC0 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UASM_i_SRL (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  build_get_pgde32 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_get_pmde64 (int /*<<< orphan*/ **,struct uasm_label**,struct uasm_reloc**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct work_registers build_get_work_registers (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  build_is_huge_pte (int /*<<< orphan*/ **,struct uasm_reloc**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_tlb_probe_entry (int /*<<< orphan*/ **) ; 
 scalar_t__ cpu_has_tlbex_tlbp_race () ; 
 int /*<<< orphan*/  iPTE_LW (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  label_leave ; 
 int /*<<< orphan*/  label_tlb_huge_update ; 
 int /*<<< orphan*/  m4kc_tlbp_war () ; 
 int /*<<< orphan*/  uasm_i_andi (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uasm_i_ehb (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uasm_i_mfc0 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_nop (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uasm_il_bltz (int /*<<< orphan*/ **,struct uasm_reloc**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_l_smp_pgtable_change (struct uasm_label**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct work_registers
build_r4000_tlbchange_handler_head(u32 **p, struct uasm_label **l,
				   struct uasm_reloc **r)
{
	struct work_registers wr = build_get_work_registers(p);

#ifdef CONFIG_64BIT
	build_get_pmde64(p, l, r, wr.r1, wr.r2); /* get pmd in ptr */
#else
	build_get_pgde32(p, wr.r1, wr.r2); /* get pgd in ptr */
#endif

#ifdef CONFIG_MIPS_HUGE_TLB_SUPPORT
	/*
	 * For huge tlb entries, pmd doesn't contain an address but
	 * instead contains the tlb pte. Check the PAGE_HUGE bit and
	 * see if we need to jump to huge tlb processing.
	 */
	build_is_huge_pte(p, r, wr.r1, wr.r2, label_tlb_huge_update);
#endif

	UASM_i_MFC0(p, wr.r1, C0_BADVADDR);
	UASM_i_LW(p, wr.r2, 0, wr.r2);
	UASM_i_SRL(p, wr.r1, wr.r1, PAGE_SHIFT + PTE_ORDER - PTE_T_LOG2);
	uasm_i_andi(p, wr.r1, wr.r1, (PTRS_PER_PTE - 1) << PTE_T_LOG2);
	UASM_i_ADDU(p, wr.r2, wr.r2, wr.r1);

#ifdef CONFIG_SMP
	uasm_l_smp_pgtable_change(l, *p);
#endif
	iPTE_LW(p, wr.r1, wr.r2); /* get even pte */
	if (!m4kc_tlbp_war()) {
		build_tlb_probe_entry(p);
		if (cpu_has_tlbex_tlbp_race()) {
			/* race condition happens, leaving */
			uasm_i_ehb(p);
			uasm_i_mfc0(p, wr.r3, C0_INDEX);
			uasm_il_bltz(p, r, wr.r3, label_leave);
			uasm_i_nop(p);
		}
	}
	return wr;
}