#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  int vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct TYPE_5__ {int /*<<< orphan*/  pat_mode; } ;
struct TYPE_6__ {TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PHYS_TO_DMAP (int) ; 
 int VM_PAGE_TO_PHYS (TYPE_2__*) ; 
 int X86_PG_A ; 
 int X86_PG_M ; 
 int X86_PG_RW ; 
 int X86_PG_V ; 
 int dmaplimit ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int pmap_cache_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_store (scalar_t__*,int) ; 
 int /*<<< orphan*/  qframe ; 
 int /*<<< orphan*/  qframe_mtx ; 
 scalar_t__* vtopte (int /*<<< orphan*/ ) ; 

vm_offset_t
pmap_quick_enter_page(vm_page_t m)
{
	vm_paddr_t paddr;

	paddr = VM_PAGE_TO_PHYS(m);
	if (paddr < dmaplimit)
		return (PHYS_TO_DMAP(paddr));
	mtx_lock_spin(&qframe_mtx);
	KASSERT(*vtopte(qframe) == 0, ("qframe busy"));
	pte_store(vtopte(qframe), paddr | X86_PG_RW | X86_PG_V | X86_PG_A |
	    X86_PG_M | pmap_cache_bits(kernel_pmap, m->md.pat_mode, 0));
	return (qframe);
}