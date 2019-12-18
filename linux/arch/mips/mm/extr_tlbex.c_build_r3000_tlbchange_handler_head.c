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
 int /*<<< orphan*/  C0_CONTEXT ; 
 scalar_t__ pgd_current ; 
 int /*<<< orphan*/  uasm_i_addu (int /*<<< orphan*/ **,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  uasm_i_andi (int /*<<< orphan*/ **,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  uasm_i_lui (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_lw (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  uasm_i_mfc0 (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_sll (int /*<<< orphan*/ **,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  uasm_i_srl (int /*<<< orphan*/ **,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  uasm_i_tlbp (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uasm_rel_hi (long) ; 
 int /*<<< orphan*/  uasm_rel_lo (long) ; 

__attribute__((used)) static void
build_r3000_tlbchange_handler_head(u32 **p, unsigned int pte,
				   unsigned int ptr)
{
	long pgdc = (long)pgd_current;

	uasm_i_mfc0(p, pte, C0_BADVADDR);
	uasm_i_lui(p, ptr, uasm_rel_hi(pgdc)); /* cp0 delay */
	uasm_i_lw(p, ptr, uasm_rel_lo(pgdc), ptr);
	uasm_i_srl(p, pte, pte, 22); /* load delay */
	uasm_i_sll(p, pte, pte, 2);
	uasm_i_addu(p, ptr, ptr, pte);
	uasm_i_mfc0(p, pte, C0_CONTEXT);
	uasm_i_lw(p, ptr, 0, ptr); /* cp0 delay */
	uasm_i_andi(p, pte, pte, 0xffc); /* load delay */
	uasm_i_addu(p, ptr, ptr, pte);
	uasm_i_lw(p, pte, 0, ptr);
	uasm_i_tlbp(p); /* load delay */
}