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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int* vm_offset_t ;

/* Variables and functions */
 int* PCPU_GET (int /*<<< orphan*/ ) ; 
 int PTE_C_CACHE ; 
 int PTE_D ; 
 int PTE_G ; 
 int PTE_V ; 
 int TLBLO_PA_TO_PFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmap1_addr ; 
 int /*<<< orphan*/  cmap1_ptep ; 
 int /*<<< orphan*/  critical_enter () ; 

__attribute__((used)) static __inline vm_offset_t
pmap_lmem_map1(vm_paddr_t phys)
{
	critical_enter();
	*PCPU_GET(cmap1_ptep) =
	    TLBLO_PA_TO_PFN(phys) | PTE_C_CACHE | PTE_D | PTE_V | PTE_G;
	return (PCPU_GET(cmap1_addr));
}