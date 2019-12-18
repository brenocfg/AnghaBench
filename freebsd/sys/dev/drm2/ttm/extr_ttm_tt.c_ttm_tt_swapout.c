#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int /*<<< orphan*/ * vm_object_t ;
struct ttm_tt {scalar_t__ state; scalar_t__ caching_state; int num_pages; int /*<<< orphan*/  page_flags; int /*<<< orphan*/ * swap_storage; TYPE_2__* bdev; int /*<<< orphan*/ ** pages; } ;
struct TYPE_6__ {int /*<<< orphan*/  td_ucred; } ;
struct TYPE_5__ {TYPE_1__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ttm_tt_unpopulate ) (struct ttm_tt*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IDX_TO_OFF (int) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  OBJT_SWAP ; 
 int /*<<< orphan*/  TTM_PAGE_FLAG_PERSISTENT_SWAP ; 
 int /*<<< orphan*/  TTM_PAGE_FLAG_SWAPPED ; 
 int /*<<< orphan*/  VM_ALLOC_NORMAL ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_PROT_DEFAULT ; 
 TYPE_3__* curthread ; 
 int /*<<< orphan*/  pmap_copy_page (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stub1 (struct ttm_tt*) ; 
 scalar_t__ tt_cached ; 
 scalar_t__ tt_unbound ; 
 scalar_t__ tt_unpopulated ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_pip_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vm_object_pip_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_dirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vm_page_grab (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_xunbusy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vm_pager_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ttm_tt_swapout(struct ttm_tt *ttm, vm_object_t persistent_swap_storage)
{
	vm_object_t obj;
	vm_page_t from_page, to_page;
	int i;

	MPASS(ttm->state == tt_unbound || ttm->state == tt_unpopulated);
	MPASS(ttm->caching_state == tt_cached);

	if (persistent_swap_storage == NULL) {
		obj = vm_pager_allocate(OBJT_SWAP, NULL,
		    IDX_TO_OFF(ttm->num_pages), VM_PROT_DEFAULT, 0,
		    curthread->td_ucred);
		if (obj == NULL) {
			printf("[TTM] Failed allocating swap storage\n");
			return (-ENOMEM);
		}
	} else
		obj = persistent_swap_storage;

	VM_OBJECT_WLOCK(obj);
	vm_object_pip_add(obj, 1);
	for (i = 0; i < ttm->num_pages; ++i) {
		from_page = ttm->pages[i];
		if (unlikely(from_page == NULL))
			continue;
		to_page = vm_page_grab(obj, i, VM_ALLOC_NORMAL);
		pmap_copy_page(from_page, to_page);
		vm_page_valid(to_page);
		vm_page_dirty(to_page);
		vm_page_xunbusy(to_page);
	}
	vm_object_pip_wakeup(obj);
	VM_OBJECT_WUNLOCK(obj);

	ttm->bdev->driver->ttm_tt_unpopulate(ttm);
	ttm->swap_storage = obj;
	ttm->page_flags |= TTM_PAGE_FLAG_SWAPPED;
	if (persistent_swap_storage != NULL)
		ttm->page_flags |= TTM_PAGE_FLAG_PERSISTENT_SWAP;
	return (0);
}