#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct pv_chunk {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  phys_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAP_TO_PHYS (int /*<<< orphan*/ ) ; 
 TYPE_1__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PV_STAT (int /*<<< orphan*/ ) ; 
 int _NPCPV ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dump_drop_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pc_chunk_count ; 
 int /*<<< orphan*/  pc_chunk_frees ; 
 int /*<<< orphan*/  pv_entry_spare ; 
 int /*<<< orphan*/  vm_page_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_unwire_noq (TYPE_1__*) ; 

__attribute__((used)) static void
free_pv_chunk_dequeued(struct pv_chunk *pc)
{
	vm_page_t m;

	PV_STAT(atomic_subtract_int(&pv_entry_spare, _NPCPV));
	PV_STAT(atomic_subtract_int(&pc_chunk_count, 1));
	PV_STAT(atomic_add_int(&pc_chunk_frees, 1));
	/* entire chunk is free, return it */
	m = PHYS_TO_VM_PAGE(DMAP_TO_PHYS((vm_offset_t)pc));
	dump_drop_page(m->phys_addr);
	vm_page_unwire_noq(m);
	vm_page_free(m);
}