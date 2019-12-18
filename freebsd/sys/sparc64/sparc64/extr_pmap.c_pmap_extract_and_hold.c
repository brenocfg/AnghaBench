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
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct tte {int tte_data; } ;
typedef  scalar_t__ pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/ * PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (scalar_t__) ; 
 int TD_SW ; 
 int TD_V ; 
 int /*<<< orphan*/  TLB_DIRECT_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTE_GET_PA (struct tte*) ; 
 int /*<<< orphan*/  VM_MIN_DIRECT_ADDRESS ; 
 int VM_PROT_WRITE ; 
 scalar_t__ kernel_pmap ; 
 struct tte* tsb_kvtotte (int /*<<< orphan*/ ) ; 
 struct tte* tsb_tte_lookup (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_wire_mapped (int /*<<< orphan*/ *) ; 

vm_page_t
pmap_extract_and_hold(pmap_t pm, vm_offset_t va, vm_prot_t prot)
{
	struct tte *tp;
	vm_page_t m;

	m = NULL;
	PMAP_LOCK(pm);
	if (pm == kernel_pmap) {
		if (va >= VM_MIN_DIRECT_ADDRESS) {
			tp = NULL;
			m = PHYS_TO_VM_PAGE(TLB_DIRECT_TO_PHYS(va));
			if (!vm_page_wire_mapped(m))
				m = NULL;
		} else {
			tp = tsb_kvtotte(va);
			if ((tp->tte_data & TD_V) == 0)
				tp = NULL;
		}
	} else
		tp = tsb_tte_lookup(pm, va);
	if (tp != NULL && ((tp->tte_data & TD_SW) ||
	    (prot & VM_PROT_WRITE) == 0)) {
		m = PHYS_TO_VM_PAGE(TTE_GET_PA(tp));
		if (!vm_page_wire_mapped(m))
			m = NULL;
	}
	PMAP_UNLOCK(pm);
	return (m);
}