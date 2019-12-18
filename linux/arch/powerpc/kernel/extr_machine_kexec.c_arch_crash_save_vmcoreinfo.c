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

/* Variables and functions */
 int /*<<< orphan*/  MAX_NUMNODES ; 
 int /*<<< orphan*/  VMCOREINFO_LENGTH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMCOREINFO_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMCOREINFO_STRUCT_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMCOREINFO_SYMBOL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  contig_page_data ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  mmu_psize_def ; 
 int /*<<< orphan*/  mmu_psize_defs ; 
 int /*<<< orphan*/  mmu_vmemmap_psize ; 
 int /*<<< orphan*/  node_data ; 
 int /*<<< orphan*/  phys ; 
 int /*<<< orphan*/  shift ; 
 int /*<<< orphan*/  virt_addr ; 
 int /*<<< orphan*/  vmemmap_backing ; 
 int /*<<< orphan*/  vmemmap_list ; 

void arch_crash_save_vmcoreinfo(void)
{

#ifdef CONFIG_NEED_MULTIPLE_NODES
	VMCOREINFO_SYMBOL(node_data);
	VMCOREINFO_LENGTH(node_data, MAX_NUMNODES);
#endif
#ifndef CONFIG_NEED_MULTIPLE_NODES
	VMCOREINFO_SYMBOL(contig_page_data);
#endif
#if defined(CONFIG_PPC64) && defined(CONFIG_SPARSEMEM_VMEMMAP)
	VMCOREINFO_SYMBOL(vmemmap_list);
	VMCOREINFO_SYMBOL(mmu_vmemmap_psize);
	VMCOREINFO_SYMBOL(mmu_psize_defs);
	VMCOREINFO_STRUCT_SIZE(vmemmap_backing);
	VMCOREINFO_OFFSET(vmemmap_backing, list);
	VMCOREINFO_OFFSET(vmemmap_backing, phys);
	VMCOREINFO_OFFSET(vmemmap_backing, virt_addr);
	VMCOREINFO_STRUCT_SIZE(mmu_psize_def);
	VMCOREINFO_OFFSET(mmu_psize_def, shift);
#endif
}