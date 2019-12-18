#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  scalar_t__ vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
struct rwlock {int dummy; } ;
typedef  int /*<<< orphan*/  pmap_t ;
struct TYPE_9__ {scalar_t__ pindex; int psind; int /*<<< orphan*/  object; } ;

/* Variables and functions */
 scalar_t__ L2_OFFSET ; 
 scalar_t__ L2_SIZE ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_LOCKED (int /*<<< orphan*/ ) ; 
 scalar_t__ atop (scalar_t__) ; 
 int /*<<< orphan*/  listq ; 
 scalar_t__ pmap_enter_2mpage (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,struct rwlock**) ; 
 TYPE_1__* pmap_enter_quick_locked (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,struct rwlock**) ; 
 scalar_t__ pmap_ps_enabled (int /*<<< orphan*/ ) ; 
 scalar_t__ ptoa (scalar_t__) ; 
 int /*<<< orphan*/  rw_wunlock (struct rwlock*) ; 

void
pmap_enter_object(pmap_t pmap, vm_offset_t start, vm_offset_t end,
    vm_page_t m_start, vm_prot_t prot)
{
	struct rwlock *lock;
	vm_offset_t va;
	vm_page_t m, mpte;
	vm_pindex_t diff, psize;

	VM_OBJECT_ASSERT_LOCKED(m_start->object);

	psize = atop(end - start);
	mpte = NULL;
	m = m_start;
	lock = NULL;
	PMAP_LOCK(pmap);
	while (m != NULL && (diff = m->pindex - m_start->pindex) < psize) {
		va = start + ptoa(diff);
		if ((va & L2_OFFSET) == 0 && va + L2_SIZE <= end &&
		    m->psind == 1 && pmap_ps_enabled(pmap) &&
		    pmap_enter_2mpage(pmap, va, m, prot, &lock))
			m = &m[L2_SIZE / PAGE_SIZE - 1];
		else
			mpte = pmap_enter_quick_locked(pmap, va, m, prot, mpte,
			    &lock);
		m = TAILQ_NEXT(m, listq);
	}
	if (lock != NULL)
		rw_wunlock(lock);
	PMAP_UNLOCK(pmap);
}