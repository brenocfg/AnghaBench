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
struct vmemmap_backing {struct vmemmap_backing* list; int /*<<< orphan*/  virt_addr; } ;
struct pg_state {int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SPARSEMEM_VMEMMAP ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpte_find (struct pg_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_vmemmap_psize ; 
 int /*<<< orphan*/  seq_puts (int /*<<< orphan*/ ,char*) ; 
 struct vmemmap_backing* vmemmap_list ; 

__attribute__((used)) static void walk_vmemmap(struct pg_state *st)
{
	struct vmemmap_backing *ptr = vmemmap_list;

	if (!IS_ENABLED(CONFIG_SPARSEMEM_VMEMMAP))
		return;
	/*
	 * Traverse the vmemmaped memory and dump pages that are in the hash
	 * pagetable.
	 */
	while (ptr->list) {
		hpte_find(st, ptr->virt_addr, mmu_vmemmap_psize);
		ptr = ptr->list;
	}
	seq_puts(st->seq, "---[ vmemmap end ]---\n");
}