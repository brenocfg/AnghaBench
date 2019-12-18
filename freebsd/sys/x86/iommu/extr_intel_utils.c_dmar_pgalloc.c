#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int DMAR_PGF_NOALLOC ; 
 int DMAR_PGF_OBJL ; 
 int DMAR_PGF_WAITOK ; 
 int DMAR_PGF_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PG_ZERO ; 
 int VM_ALLOC_NOBUSY ; 
 int VM_ALLOC_NODUMP ; 
 int VM_ALLOC_NOWAIT ; 
 int VM_ALLOC_SYSTEM ; 
 int VM_ALLOC_WAITFAIL ; 
 int VM_ALLOC_ZERO ; 
 int /*<<< orphan*/  VM_MEMATTR_DEFAULT ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dmar_high ; 
 int /*<<< orphan*/  dmar_tbl_pagecnt ; 
 int /*<<< orphan*/  pmap_zero_page (TYPE_1__*) ; 
 TYPE_1__* vm_page_alloc_contig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* vm_page_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

vm_page_t
dmar_pgalloc(vm_object_t obj, vm_pindex_t idx, int flags)
{
	vm_page_t m;
	int zeroed, aflags;

	zeroed = (flags & DMAR_PGF_ZERO) != 0 ? VM_ALLOC_ZERO : 0;
	aflags = zeroed | VM_ALLOC_NOBUSY | VM_ALLOC_SYSTEM | VM_ALLOC_NODUMP |
	    ((flags & DMAR_PGF_WAITOK) != 0 ? VM_ALLOC_WAITFAIL :
	    VM_ALLOC_NOWAIT);
	for (;;) {
		if ((flags & DMAR_PGF_OBJL) == 0)
			VM_OBJECT_WLOCK(obj);
		m = vm_page_lookup(obj, idx);
		if ((flags & DMAR_PGF_NOALLOC) != 0 || m != NULL) {
			if ((flags & DMAR_PGF_OBJL) == 0)
				VM_OBJECT_WUNLOCK(obj);
			break;
		}
		m = vm_page_alloc_contig(obj, idx, aflags, 1, 0,
		    dmar_high, PAGE_SIZE, 0, VM_MEMATTR_DEFAULT);
		if ((flags & DMAR_PGF_OBJL) == 0)
			VM_OBJECT_WUNLOCK(obj);
		if (m != NULL) {
			if (zeroed && (m->flags & PG_ZERO) == 0)
				pmap_zero_page(m);
			atomic_add_int(&dmar_tbl_pagecnt, 1);
			break;
		}
		if ((flags & DMAR_PGF_WAITOK) == 0)
			break;
	}
	return (m);
}