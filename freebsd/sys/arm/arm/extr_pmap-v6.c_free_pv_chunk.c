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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct pv_chunk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PV_STAT (scalar_t__) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pv_chunk*,int /*<<< orphan*/ ) ; 
 scalar_t__ _NPCPV ; 
 int /*<<< orphan*/  pc_chunk_count ; 
 int /*<<< orphan*/  pc_chunk_frees ; 
 int /*<<< orphan*/  pc_lru ; 
 int /*<<< orphan*/  pmap_kextract (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_pte2list_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_qremove (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pv_chunks ; 
 int /*<<< orphan*/  pv_entry_spare ; 
 int /*<<< orphan*/  pv_vafree ; 
 int /*<<< orphan*/  vm_page_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_unwire_noq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_pv_chunk(struct pv_chunk *pc)
{
	vm_page_t m;

	TAILQ_REMOVE(&pv_chunks, pc, pc_lru);
	PV_STAT(pv_entry_spare -= _NPCPV);
	PV_STAT(pc_chunk_count--);
	PV_STAT(pc_chunk_frees++);
	/* entire chunk is free, return it */
	m = PHYS_TO_VM_PAGE(pmap_kextract((vm_offset_t)pc));
	pmap_qremove((vm_offset_t)pc, 1);
	vm_page_unwire_noq(m);
	vm_page_free(m);
	pmap_pte2list_free(&pv_vafree, (vm_offset_t)pc);
}