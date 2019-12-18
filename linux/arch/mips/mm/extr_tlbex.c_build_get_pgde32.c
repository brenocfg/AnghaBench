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

/* Variables and functions */
 int /*<<< orphan*/  C0_BADVADDR ; 
 int /*<<< orphan*/  PGDIR_SHIFT ; 
 int /*<<< orphan*/  PGD_T_LOG2 ; 
 int /*<<< orphan*/  SMP_CPUID_PTRSHIFT ; 
 int /*<<< orphan*/  SMP_CPUID_REG ; 
 int /*<<< orphan*/  UASM_i_LA_mostly (int /*<<< orphan*/ **,unsigned int,long) ; 
 int /*<<< orphan*/  c0_kscratch () ; 
 scalar_t__ pgd_current ; 
 int pgd_reg ; 
 int /*<<< orphan*/  uasm_i_addu (int /*<<< orphan*/ **,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  uasm_i_lw (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  uasm_i_mfc0 (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  uasm_i_sll (int /*<<< orphan*/ **,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_srl (int /*<<< orphan*/ **,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_rel_lo (long) ; 

void build_get_pgde32(u32 **p, unsigned int tmp, unsigned int ptr)
{
	if (pgd_reg != -1) {
		/* pgd is in pgd_reg */
		uasm_i_mfc0(p, ptr, c0_kscratch(), pgd_reg);
		uasm_i_mfc0(p, tmp, C0_BADVADDR); /* get faulting address */
	} else {
		long pgdc = (long)pgd_current;

		/* 32 bit SMP has smp_processor_id() stored in CONTEXT. */
#ifdef CONFIG_SMP
		uasm_i_mfc0(p, ptr, SMP_CPUID_REG);
		UASM_i_LA_mostly(p, tmp, pgdc);
		uasm_i_srl(p, ptr, ptr, SMP_CPUID_PTRSHIFT);
		uasm_i_addu(p, ptr, tmp, ptr);
#else
		UASM_i_LA_mostly(p, ptr, pgdc);
#endif
		uasm_i_mfc0(p, tmp, C0_BADVADDR); /* get faulting address */
		uasm_i_lw(p, ptr, uasm_rel_lo(pgdc), ptr);
	}
	uasm_i_srl(p, tmp, tmp, PGDIR_SHIFT); /* get pgd only bits */
	uasm_i_sll(p, tmp, tmp, PGD_T_LOG2);
	uasm_i_addu(p, ptr, ptr, tmp); /* add in pgd offset */
}