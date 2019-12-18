#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  scalar_t__ vm_pindex_t ;
typedef  int vm_ooffset_t ;
typedef  TYPE_1__* vm_object_t ;
struct ucred {int dummy; } ;
struct TYPE_8__ {scalar_t__ size; void* handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJT_PHYS ; 
 int /*<<< orphan*/  OBJ_POPULATE ; 
 scalar_t__ OFF_TO_IDX (int) ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pager_object_list ; 
 int /*<<< orphan*/  phys_pager_mtx ; 
 int /*<<< orphan*/  phys_pager_object_list ; 
 TYPE_1__* vm_object_allocate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vm_object_deallocate (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_set_flag (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* vm_pager_object_lookup (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static vm_object_t
phys_pager_alloc(void *handle, vm_ooffset_t size, vm_prot_t prot,
    vm_ooffset_t foff, struct ucred *cred)
{
	vm_object_t object, object1;
	vm_pindex_t pindex;

	/*
	 * Offset should be page aligned.
	 */
	if (foff & PAGE_MASK)
		return (NULL);

	pindex = OFF_TO_IDX(foff + PAGE_MASK + size);

	if (handle != NULL) {
		mtx_lock(&phys_pager_mtx);
		/*
		 * Look up pager, creating as necessary.
		 */
		object1 = NULL;
		object = vm_pager_object_lookup(&phys_pager_object_list, handle);
		if (object == NULL) {
			/*
			 * Allocate object and associate it with the pager.
			 */
			mtx_unlock(&phys_pager_mtx);
			object1 = vm_object_allocate(OBJT_PHYS, pindex);
			mtx_lock(&phys_pager_mtx);
			object = vm_pager_object_lookup(&phys_pager_object_list,
			    handle);
			if (object != NULL) {
				/*
				 * We raced with other thread while
				 * allocating object.
				 */
				if (pindex > object->size)
					object->size = pindex;
			} else {
				object = object1;
				object1 = NULL;
				object->handle = handle;
				vm_object_set_flag(object, OBJ_POPULATE);
				TAILQ_INSERT_TAIL(&phys_pager_object_list,
				    object, pager_object_list);
			}
		} else {
			if (pindex > object->size)
				object->size = pindex;
		}
		mtx_unlock(&phys_pager_mtx);
		vm_object_deallocate(object1);
	} else {
		object = vm_object_allocate(OBJT_PHYS, pindex);
		vm_object_set_flag(object, OBJ_POPULATE);
	}

	return (object);
}