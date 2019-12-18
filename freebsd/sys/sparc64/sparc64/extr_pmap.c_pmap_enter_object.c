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
typedef  int vm_prot_t ;
typedef  scalar_t__ vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  pmap_t ;
struct TYPE_6__ {scalar_t__ pindex; int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMAP_ENTER_QUICK_LOCKED ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_LOCKED (int /*<<< orphan*/ ) ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 scalar_t__ atop (scalar_t__) ; 
 int /*<<< orphan*/  listq ; 
 int /*<<< orphan*/  pmap_enter_locked (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ptoa (scalar_t__) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tte_list_global_lock ; 

void
pmap_enter_object(pmap_t pm, vm_offset_t start, vm_offset_t end,
    vm_page_t m_start, vm_prot_t prot)
{
	vm_page_t m;
	vm_pindex_t diff, psize;

	VM_OBJECT_ASSERT_LOCKED(m_start->object);

	psize = atop(end - start);
	m = m_start;
	rw_wlock(&tte_list_global_lock);
	PMAP_LOCK(pm);
	while (m != NULL && (diff = m->pindex - m_start->pindex) < psize) {
		pmap_enter_locked(pm, start + ptoa(diff), m, prot &
		    (VM_PROT_READ | VM_PROT_EXECUTE),
		    PMAP_ENTER_QUICK_LOCKED, 0);
		m = TAILQ_NEXT(m, listq);
	}
	rw_wunlock(&tte_list_global_lock);
	PMAP_UNLOCK(pm);
}