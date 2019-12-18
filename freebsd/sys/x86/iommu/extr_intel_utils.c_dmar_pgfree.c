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
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;

/* Variables and functions */
 int DMAR_PGF_OBJL ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dmar_tbl_pagecnt ; 
 int /*<<< orphan*/  vm_page_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vm_page_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dmar_pgfree(vm_object_t obj, vm_pindex_t idx, int flags)
{
	vm_page_t m;

	if ((flags & DMAR_PGF_OBJL) == 0)
		VM_OBJECT_WLOCK(obj);
	m = vm_page_lookup(obj, idx);
	if (m != NULL) {
		vm_page_free(m);
		atomic_subtract_int(&dmar_tbl_pagecnt, 1);
	}
	if ((flags & DMAR_PGF_OBJL) == 0)
		VM_OBJECT_WUNLOCK(obj);
}