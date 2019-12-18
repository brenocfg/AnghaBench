#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  pt2_entry_t ;
typedef  scalar_t__ pmap_t ;
struct TYPE_7__ {scalar_t__ pat_mode; } ;
struct TYPE_8__ {TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTE2_KPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTE2_KPT_NG (int /*<<< orphan*/ ) ; 
 scalar_t__ kernel_pmap ; 
 int /*<<< orphan*/  pmap_kenter_pt2tab (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_page_set_memattr (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  pmap_pt2pg_zero (TYPE_2__*) ; 
 int /*<<< orphan*/ * pmap_pt2tab_entry (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt2_wirecount_init (TYPE_2__*) ; 
 int /*<<< orphan*/  pt2tab_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pt_memattr ; 

__attribute__((used)) static __inline vm_paddr_t
pmap_pt2pg_init(pmap_t pmap, vm_offset_t va, vm_page_t m)
{
	vm_paddr_t pa;
	pt2_entry_t *pte2p;

	/* Check page attributes. */
	if (m->md.pat_mode != pt_memattr)
		pmap_page_set_memattr(m, pt_memattr);

	/* Zero page and init wire counts. */
	pa = pmap_pt2pg_zero(m);
	pt2_wirecount_init(m);

	/*
	 * Map page to PT2MAP address space for given pmap.
	 * Note that PT2MAP space is shared with all pmaps.
	 */
	if (pmap == kernel_pmap)
		pmap_kenter_pt2tab(va, PTE2_KPT(pa));
	else {
		pte2p = pmap_pt2tab_entry(pmap, va);
		pt2tab_store(pte2p, PTE2_KPT_NG(pa));
	}

	return (pa);
}