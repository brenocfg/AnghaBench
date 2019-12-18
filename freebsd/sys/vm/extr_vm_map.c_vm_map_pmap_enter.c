#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_size_t ;
typedef  int vm_prot_t ;
typedef  scalar_t__ vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  int vm_offset_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  TYPE_3__* vm_map_t ;
struct TYPE_21__ {int /*<<< orphan*/  pmap; } ;
struct TYPE_20__ {scalar_t__ type; scalar_t__ size; } ;
struct TYPE_19__ {scalar_t__ pindex; size_t psind; } ;

/* Variables and functions */
 int MAP_PREFAULT_MADVISE ; 
 int MAP_PREFAULT_PARTIAL ; 
 scalar_t__ MAX_INIT_PT ; 
 scalar_t__ OBJT_DEVICE ; 
 scalar_t__ OBJT_SG ; 
 int /*<<< orphan*/  PS_ALL_VALID ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_LOCK_DOWNGRADE (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_RLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_RUNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_2__*) ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 scalar_t__ atop (int) ; 
 int /*<<< orphan*/  listq ; 
 int* pagesizes ; 
 int /*<<< orphan*/  pmap_enter_object (int /*<<< orphan*/ ,int,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pmap_object_init_pt (int /*<<< orphan*/ ,int,TYPE_2__*,scalar_t__,int) ; 
 int ptoa (scalar_t__) ; 
 scalar_t__ vm_page_all_valid (TYPE_1__*) ; 
 scalar_t__ vm_page_count_severe () ; 
 TYPE_1__* vm_page_find_least (TYPE_2__*,scalar_t__) ; 
 scalar_t__ vm_page_ps_test (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vm_map_pmap_enter(vm_map_t map, vm_offset_t addr, vm_prot_t prot,
    vm_object_t object, vm_pindex_t pindex, vm_size_t size, int flags)
{
	vm_offset_t start;
	vm_page_t p, p_start;
	vm_pindex_t mask, psize, threshold, tmpidx;

	if ((prot & (VM_PROT_READ | VM_PROT_EXECUTE)) == 0 || object == NULL)
		return;
	VM_OBJECT_RLOCK(object);
	if (object->type == OBJT_DEVICE || object->type == OBJT_SG) {
		VM_OBJECT_RUNLOCK(object);
		VM_OBJECT_WLOCK(object);
		if (object->type == OBJT_DEVICE || object->type == OBJT_SG) {
			pmap_object_init_pt(map->pmap, addr, object, pindex,
			    size);
			VM_OBJECT_WUNLOCK(object);
			return;
		}
		VM_OBJECT_LOCK_DOWNGRADE(object);
	}

	psize = atop(size);
	if (psize + pindex > object->size) {
		if (object->size < pindex) {
			VM_OBJECT_RUNLOCK(object);
			return;
		}
		psize = object->size - pindex;
	}

	start = 0;
	p_start = NULL;
	threshold = MAX_INIT_PT;

	p = vm_page_find_least(object, pindex);
	/*
	 * Assert: the variable p is either (1) the page with the
	 * least pindex greater than or equal to the parameter pindex
	 * or (2) NULL.
	 */
	for (;
	     p != NULL && (tmpidx = p->pindex - pindex) < psize;
	     p = TAILQ_NEXT(p, listq)) {
		/*
		 * don't allow an madvise to blow away our really
		 * free pages allocating pv entries.
		 */
		if (((flags & MAP_PREFAULT_MADVISE) != 0 &&
		    vm_page_count_severe()) ||
		    ((flags & MAP_PREFAULT_PARTIAL) != 0 &&
		    tmpidx >= threshold)) {
			psize = tmpidx;
			break;
		}
		if (vm_page_all_valid(p)) {
			if (p_start == NULL) {
				start = addr + ptoa(tmpidx);
				p_start = p;
			}
			/* Jump ahead if a superpage mapping is possible. */
			if (p->psind > 0 && ((addr + ptoa(tmpidx)) &
			    (pagesizes[p->psind] - 1)) == 0) {
				mask = atop(pagesizes[p->psind]) - 1;
				if (tmpidx + mask < psize &&
				    vm_page_ps_test(p, PS_ALL_VALID, NULL)) {
					p += mask;
					threshold += mask;
				}
			}
		} else if (p_start != NULL) {
			pmap_enter_object(map->pmap, start, addr +
			    ptoa(tmpidx), p_start, prot);
			p_start = NULL;
		}
	}
	if (p_start != NULL)
		pmap_enter_object(map->pmap, start, addr + ptoa(psize),
		    p_start, prot);
	VM_OBJECT_RUNLOCK(object);
}