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
struct uasm_reloc {int dummy; } ;
struct uasm_label {int dummy; } ;
struct mips_huge_tlb_info {int huge_pte; int restore_scratch; int need_reload_pte; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  C0_BADVADDR ; 
 int /*<<< orphan*/  C0_CONTEXT ; 
 int /*<<< orphan*/  C0_ENTRYLO0 ; 
 int /*<<< orphan*/  C0_ENTRYLO1 ; 
 int /*<<< orphan*/  GET_CONTEXT (int /*<<< orphan*/ **,unsigned int) ; 
 unsigned int LOC_PTEP ; 
 int PAGE_SHIFT ; 
 int PGDIR_SHIFT ; 
 int PGD_ORDER ; 
 int PMD_SHIFT ; 
 int PTRS_PER_PGD ; 
 int PTRS_PER_PMD ; 
 int PTRS_PER_PUD ; 
 int PUD_SHIFT ; 
 int /*<<< orphan*/  UASM_i_ADDIU (int /*<<< orphan*/ **,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  UASM_i_ADDU (int /*<<< orphan*/ **,unsigned int,int const,unsigned int) ; 
 int /*<<< orphan*/  UASM_i_LW (int /*<<< orphan*/ **,int const,int,unsigned int) ; 
 int /*<<< orphan*/  UASM_i_LWX (int /*<<< orphan*/ **,int const,int const,unsigned int) ; 
 int /*<<< orphan*/  UASM_i_MFC0 (int /*<<< orphan*/ **,int const,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  UASM_i_MTC0 (int /*<<< orphan*/ **,int const,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  UASM_i_SW (int /*<<< orphan*/ **,int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _PAGE_GLOBAL ; 
 int /*<<< orphan*/  _PAGE_HUGE ; 
 int /*<<< orphan*/  build_adjust_context (int /*<<< orphan*/ **,unsigned int) ; 
 int /*<<< orphan*/  build_tlb_write_entry (int /*<<< orphan*/ **,struct uasm_label**,struct uasm_reloc**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c0_kscratch () ; 
 scalar_t__ check_for_high_segbits ; 
 scalar_t__ cpu_has_rixi ; 
 int ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  label_tlb_huge_update ; 
 int /*<<< orphan*/  label_vmalloc ; 
 int pgd_reg ; 
 int scratchpad_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlb_random ; 
 int /*<<< orphan*/  uasm_i_andi (int /*<<< orphan*/ **,int const,int const,int) ; 
 int /*<<< orphan*/  uasm_i_daddu (int /*<<< orphan*/ **,unsigned int,unsigned int,int const) ; 
 int /*<<< orphan*/  uasm_i_dins (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uasm_i_drotr (int /*<<< orphan*/ **,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  uasm_i_dsrl_safe (int /*<<< orphan*/ **,int const,unsigned int,int) ; 
 int /*<<< orphan*/  uasm_i_ehb (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uasm_i_eret (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uasm_i_ld (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  uasm_i_nop (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uasm_i_ori (int /*<<< orphan*/ **,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  uasm_il_bbit1 (int /*<<< orphan*/ **,struct uasm_reloc**,int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_il_bltz (int /*<<< orphan*/ **,struct uasm_reloc**,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_il_bnez (int /*<<< orphan*/ **,struct uasm_reloc**,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_l_leave (struct uasm_label**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uasm_l_vmalloc_done (struct uasm_label**,int /*<<< orphan*/ *) ; 
 scalar_t__ use_lwx_insns () ; 

__attribute__((used)) static struct mips_huge_tlb_info
build_fast_tlb_refill_handler (u32 **p, struct uasm_label **l,
			       struct uasm_reloc **r, unsigned int tmp,
			       unsigned int ptr, int c0_scratch_reg)
{
	struct mips_huge_tlb_info rv;
	unsigned int even, odd;
	int vmalloc_branch_delay_filled = 0;
	const int scratch = 1; /* Our extra working register */

	rv.huge_pte = scratch;
	rv.restore_scratch = 0;
	rv.need_reload_pte = false;

	if (check_for_high_segbits) {
		UASM_i_MFC0(p, tmp, C0_BADVADDR);

		if (pgd_reg != -1)
			UASM_i_MFC0(p, ptr, c0_kscratch(), pgd_reg);
		else
			UASM_i_MFC0(p, ptr, C0_CONTEXT);

		if (c0_scratch_reg >= 0)
			UASM_i_MTC0(p, scratch, c0_kscratch(), c0_scratch_reg);
		else
			UASM_i_SW(p, scratch, scratchpad_offset(0), 0);

		uasm_i_dsrl_safe(p, scratch, tmp,
				 PGDIR_SHIFT + PGD_ORDER + PAGE_SHIFT - 3);
		uasm_il_bnez(p, r, scratch, label_vmalloc);

		if (pgd_reg == -1) {
			vmalloc_branch_delay_filled = 1;
			/* Clear lower 23 bits of context. */
			uasm_i_dins(p, ptr, 0, 0, 23);
		}
	} else {
		if (pgd_reg != -1)
			UASM_i_MFC0(p, ptr, c0_kscratch(), pgd_reg);
		else
			UASM_i_MFC0(p, ptr, C0_CONTEXT);

		UASM_i_MFC0(p, tmp, C0_BADVADDR);

		if (c0_scratch_reg >= 0)
			UASM_i_MTC0(p, scratch, c0_kscratch(), c0_scratch_reg);
		else
			UASM_i_SW(p, scratch, scratchpad_offset(0), 0);

		if (pgd_reg == -1)
			/* Clear lower 23 bits of context. */
			uasm_i_dins(p, ptr, 0, 0, 23);

		uasm_il_bltz(p, r, tmp, label_vmalloc);
	}

	if (pgd_reg == -1) {
		vmalloc_branch_delay_filled = 1;
		/* 1 0	1 0 1  << 6  xkphys cached */
		uasm_i_ori(p, ptr, ptr, 0x540);
		uasm_i_drotr(p, ptr, ptr, 11);
	}

#ifdef __PAGETABLE_PMD_FOLDED
#define LOC_PTEP scratch
#else
#define LOC_PTEP ptr
#endif

	if (!vmalloc_branch_delay_filled)
		/* get pgd offset in bytes */
		uasm_i_dsrl_safe(p, scratch, tmp, PGDIR_SHIFT - 3);

	uasm_l_vmalloc_done(l, *p);

	/*
	 *			   tmp		ptr
	 * fall-through case =	 badvaddr  *pgd_current
	 * vmalloc case	     =	 badvaddr  swapper_pg_dir
	 */

	if (vmalloc_branch_delay_filled)
		/* get pgd offset in bytes */
		uasm_i_dsrl_safe(p, scratch, tmp, PGDIR_SHIFT - 3);

#ifdef __PAGETABLE_PMD_FOLDED
	GET_CONTEXT(p, tmp); /* get context reg */
#endif
	uasm_i_andi(p, scratch, scratch, (PTRS_PER_PGD - 1) << 3);

	if (use_lwx_insns()) {
		UASM_i_LWX(p, LOC_PTEP, scratch, ptr);
	} else {
		uasm_i_daddu(p, ptr, ptr, scratch); /* add in pgd offset */
		uasm_i_ld(p, LOC_PTEP, 0, ptr); /* get pmd pointer */
	}

#ifndef __PAGETABLE_PUD_FOLDED
	/* get pud offset in bytes */
	uasm_i_dsrl_safe(p, scratch, tmp, PUD_SHIFT - 3);
	uasm_i_andi(p, scratch, scratch, (PTRS_PER_PUD - 1) << 3);

	if (use_lwx_insns()) {
		UASM_i_LWX(p, ptr, scratch, ptr);
	} else {
		uasm_i_daddu(p, ptr, ptr, scratch); /* add in pmd offset */
		UASM_i_LW(p, ptr, 0, ptr);
	}
	/* ptr contains a pointer to PMD entry */
	/* tmp contains the address */
#endif

#ifndef __PAGETABLE_PMD_FOLDED
	/* get pmd offset in bytes */
	uasm_i_dsrl_safe(p, scratch, tmp, PMD_SHIFT - 3);
	uasm_i_andi(p, scratch, scratch, (PTRS_PER_PMD - 1) << 3);
	GET_CONTEXT(p, tmp); /* get context reg */

	if (use_lwx_insns()) {
		UASM_i_LWX(p, scratch, scratch, ptr);
	} else {
		uasm_i_daddu(p, ptr, ptr, scratch); /* add in pmd offset */
		UASM_i_LW(p, scratch, 0, ptr);
	}
#endif
	/* Adjust the context during the load latency. */
	build_adjust_context(p, tmp);

#ifdef CONFIG_MIPS_HUGE_TLB_SUPPORT
	uasm_il_bbit1(p, r, scratch, ilog2(_PAGE_HUGE), label_tlb_huge_update);
	/*
	 * The in the LWX case we don't want to do the load in the
	 * delay slot.	It cannot issue in the same cycle and may be
	 * speculative and unneeded.
	 */
	if (use_lwx_insns())
		uasm_i_nop(p);
#endif /* CONFIG_MIPS_HUGE_TLB_SUPPORT */


	/* build_update_entries */
	if (use_lwx_insns()) {
		even = ptr;
		odd = tmp;
		UASM_i_LWX(p, even, scratch, tmp);
		UASM_i_ADDIU(p, tmp, tmp, sizeof(pte_t));
		UASM_i_LWX(p, odd, scratch, tmp);
	} else {
		UASM_i_ADDU(p, ptr, scratch, tmp); /* add in offset */
		even = tmp;
		odd = ptr;
		UASM_i_LW(p, even, 0, ptr); /* get even pte */
		UASM_i_LW(p, odd, sizeof(pte_t), ptr); /* get odd pte */
	}
	if (cpu_has_rixi) {
		uasm_i_drotr(p, even, even, ilog2(_PAGE_GLOBAL));
		UASM_i_MTC0(p, even, C0_ENTRYLO0); /* load it */
		uasm_i_drotr(p, odd, odd, ilog2(_PAGE_GLOBAL));
	} else {
		uasm_i_dsrl_safe(p, even, even, ilog2(_PAGE_GLOBAL));
		UASM_i_MTC0(p, even, C0_ENTRYLO0); /* load it */
		uasm_i_dsrl_safe(p, odd, odd, ilog2(_PAGE_GLOBAL));
	}
	UASM_i_MTC0(p, odd, C0_ENTRYLO1); /* load it */

	if (c0_scratch_reg >= 0) {
		uasm_i_ehb(p);
		UASM_i_MFC0(p, scratch, c0_kscratch(), c0_scratch_reg);
		build_tlb_write_entry(p, l, r, tlb_random);
		uasm_l_leave(l, *p);
		rv.restore_scratch = 1;
	} else if (PAGE_SHIFT == 14 || PAGE_SHIFT == 13)  {
		build_tlb_write_entry(p, l, r, tlb_random);
		uasm_l_leave(l, *p);
		UASM_i_LW(p, scratch, scratchpad_offset(0), 0);
	} else {
		UASM_i_LW(p, scratch, scratchpad_offset(0), 0);
		build_tlb_write_entry(p, l, r, tlb_random);
		uasm_l_leave(l, *p);
		rv.restore_scratch = 1;
	}

	uasm_i_eret(p); /* return from trap */

	return rv;
}