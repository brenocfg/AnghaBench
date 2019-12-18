#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
struct sf_buf {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  pindex; } ;

/* Variables and functions */
 int DMAR_PGF_ALLOC ; 
 int DMAR_PGF_OBJL ; 
 int DMAR_PGF_WAITOK ; 
 int SFB_CPUPRIVATE ; 
 int SFB_NOWAIT ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 TYPE_1__* dmar_pgalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmar_pgfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sched_pin () ; 
 int /*<<< orphan*/  sched_unpin () ; 
 struct sf_buf* sf_buf_alloc (TYPE_1__*,int) ; 
 scalar_t__ sf_buf_kva (struct sf_buf*) ; 
 TYPE_1__* vm_page_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *
dmar_map_pgtbl(vm_object_t obj, vm_pindex_t idx, int flags,
    struct sf_buf **sf)
{
	vm_page_t m;
	bool allocated;

	if ((flags & DMAR_PGF_OBJL) == 0)
		VM_OBJECT_WLOCK(obj);
	m = vm_page_lookup(obj, idx);
	if (m == NULL && (flags & DMAR_PGF_ALLOC) != 0) {
		m = dmar_pgalloc(obj, idx, flags | DMAR_PGF_OBJL);
		allocated = true;
	} else
		allocated = false;
	if (m == NULL) {
		if ((flags & DMAR_PGF_OBJL) == 0)
			VM_OBJECT_WUNLOCK(obj);
		return (NULL);
	}
	/* Sleepable allocations cannot fail. */
	if ((flags & DMAR_PGF_WAITOK) != 0)
		VM_OBJECT_WUNLOCK(obj);
	sched_pin();
	*sf = sf_buf_alloc(m, SFB_CPUPRIVATE | ((flags & DMAR_PGF_WAITOK)
	    == 0 ? SFB_NOWAIT : 0));
	if (*sf == NULL) {
		sched_unpin();
		if (allocated) {
			VM_OBJECT_ASSERT_WLOCKED(obj);
			dmar_pgfree(obj, m->pindex, flags | DMAR_PGF_OBJL);
		}
		if ((flags & DMAR_PGF_OBJL) == 0)
			VM_OBJECT_WUNLOCK(obj);
		return (NULL);
	}
	if ((flags & (DMAR_PGF_WAITOK | DMAR_PGF_OBJL)) ==
	    (DMAR_PGF_WAITOK | DMAR_PGF_OBJL))
		VM_OBJECT_WLOCK(obj);
	else if ((flags & (DMAR_PGF_WAITOK | DMAR_PGF_OBJL)) == 0)
		VM_OBJECT_WUNLOCK(obj);
	return ((void *)sf_buf_kva(*sf));
}