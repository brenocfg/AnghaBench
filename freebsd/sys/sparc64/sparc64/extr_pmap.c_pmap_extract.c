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
typedef  int vm_offset_t ;
struct tte {int dummy; } ;
typedef  scalar_t__ pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMAP_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (scalar_t__) ; 
 int TTE_GET_PA (struct tte*) ; 
 int TTE_GET_PAGE_MASK (struct tte*) ; 
 scalar_t__ kernel_pmap ; 
 int pmap_kextract (int) ; 
 struct tte* tsb_tte_lookup (scalar_t__,int) ; 

vm_paddr_t
pmap_extract(pmap_t pm, vm_offset_t va)
{
	struct tte *tp;
	vm_paddr_t pa;

	if (pm == kernel_pmap)
		return (pmap_kextract(va));
	PMAP_LOCK(pm);
	tp = tsb_tte_lookup(pm, va);
	if (tp == NULL)
		pa = 0;
	else
		pa = TTE_GET_PA(tp) | (va & TTE_GET_PAGE_MASK(tp));
	PMAP_UNLOCK(pm);
	return (pa);
}