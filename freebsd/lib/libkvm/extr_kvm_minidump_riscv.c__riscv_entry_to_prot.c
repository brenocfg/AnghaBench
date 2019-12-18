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
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int riscv_pt_entry_t ;

/* Variables and functions */
 int RISCV_PTE_W ; 
 int RISCV_PTE_X ; 
 int /*<<< orphan*/  VM_PROT_EXECUTE ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 

__attribute__((used)) static vm_prot_t
_riscv_entry_to_prot(riscv_pt_entry_t pte)
{
	vm_prot_t prot = VM_PROT_READ;

	if ((pte & RISCV_PTE_W) != 0)
		prot |= VM_PROT_WRITE;
	if ((pte & RISCV_PTE_X) != 0)
		prot |= VM_PROT_EXECUTE;
	return prot;
}