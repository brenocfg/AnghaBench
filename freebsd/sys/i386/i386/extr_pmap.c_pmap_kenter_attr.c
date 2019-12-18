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
typedef  int vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;

/* Variables and functions */
 int PG_RW ; 
 int PG_V ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int pmap_cache_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * vtopte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
pmap_kenter_attr(vm_offset_t va, vm_paddr_t pa, int mode)
{
	pt_entry_t *pte;

	pte = vtopte(va);
	pte_store(pte, pa | PG_RW | PG_V | pmap_cache_bits(kernel_pmap,
	    mode, 0));
}