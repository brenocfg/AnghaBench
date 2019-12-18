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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  build_get_pgd_vmalloc64 (int /*<<< orphan*/ **,struct uasm_label**,struct uasm_reloc**,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_restore_work_registers (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  build_tlb_write_entry (int /*<<< orphan*/ **,struct uasm_label**,struct uasm_reloc**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_update_entries (int /*<<< orphan*/ **,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  not_refill ; 
 int /*<<< orphan*/  tlb_indexed ; 
 int /*<<< orphan*/  uasm_i_eret (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uasm_i_ori (int /*<<< orphan*/ **,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  uasm_i_xori (int /*<<< orphan*/ **,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  uasm_l_leave (struct uasm_label**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
build_r4000_tlbchange_handler_tail(u32 **p, struct uasm_label **l,
				   struct uasm_reloc **r, unsigned int tmp,
				   unsigned int ptr)
{
	uasm_i_ori(p, ptr, ptr, sizeof(pte_t));
	uasm_i_xori(p, ptr, ptr, sizeof(pte_t));
	build_update_entries(p, tmp, ptr);
	build_tlb_write_entry(p, l, r, tlb_indexed);
	uasm_l_leave(l, *p);
	build_restore_work_registers(p);
	uasm_i_eret(p); /* return from trap */

#ifdef CONFIG_64BIT
	build_get_pgd_vmalloc64(p, l, r, tmp, ptr, not_refill);
#endif
}