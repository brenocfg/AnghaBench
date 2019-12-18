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

/* Variables and functions */
 int /*<<< orphan*/  C0_ENTRYLO0 ; 
 int /*<<< orphan*/  C0_EPC ; 
 int /*<<< orphan*/  C0_INDEX ; 
 int /*<<< orphan*/  label_r3000_write_probe_fail ; 
 int /*<<< orphan*/  uasm_i_jr (int /*<<< orphan*/ **,unsigned int) ; 
 int /*<<< orphan*/  uasm_i_mfc0 (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_mtc0 (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_rfe (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uasm_i_tlbwi (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uasm_i_tlbwr (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uasm_il_bltz (int /*<<< orphan*/ **,struct uasm_reloc**,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_l_r3000_write_probe_fail (struct uasm_label**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
build_r3000_tlb_reload_write(u32 **p, struct uasm_label **l,
			     struct uasm_reloc **r, unsigned int pte,
			     unsigned int tmp)
{
	uasm_i_mfc0(p, tmp, C0_INDEX);
	uasm_i_mtc0(p, pte, C0_ENTRYLO0); /* cp0 delay */
	uasm_il_bltz(p, r, tmp, label_r3000_write_probe_fail); /* cp0 delay */
	uasm_i_mfc0(p, tmp, C0_EPC); /* branch delay */
	uasm_i_tlbwi(p); /* cp0 delay */
	uasm_i_jr(p, tmp);
	uasm_i_rfe(p); /* branch delay */
	uasm_l_r3000_write_probe_fail(l, *p);
	uasm_i_tlbwr(p); /* cp0 delay */
	uasm_i_jr(p, tmp);
	uasm_i_rfe(p); /* branch delay */
}