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
typedef  int vm_prot_t ;
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int PMAP_ENTER_NOSLEEP ; 
 int PMAP_ENTER_QUICK_LOCKED ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 int /*<<< orphan*/  moea64_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

void
moea64_enter_quick(mmu_t mmu, pmap_t pm, vm_offset_t va, vm_page_t m,
    vm_prot_t prot)
{

	moea64_enter(mmu, pm, va, m, prot & (VM_PROT_READ | VM_PROT_EXECUTE),
	    PMAP_ENTER_NOSLEEP | PMAP_ENTER_QUICK_LOCKED, 0);
}