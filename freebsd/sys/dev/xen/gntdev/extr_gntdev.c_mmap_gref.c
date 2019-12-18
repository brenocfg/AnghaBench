#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  struct vm_object* vm_object_t ;
typedef  scalar_t__ uint32_t ;
struct vm_object {int dummy; } ;
struct per_user_data {int /*<<< orphan*/  user_data_lock; int /*<<< orphan*/  gref_tree; } ;
struct gntdev_gref {int /*<<< orphan*/  file_index; TYPE_1__* page; } ;
struct TYPE_2__ {scalar_t__ object; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  OBJT_PHYS ; 
 int /*<<< orphan*/  OFF_TO_IDX (int /*<<< orphan*/ ) ; 
 struct gntdev_gref* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct gntdev_gref*) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (struct vm_object*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (struct vm_object*) ; 
 int /*<<< orphan*/  gref_tree_head ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct vm_object* vm_object_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_deallocate (struct vm_object*) ; 
 int /*<<< orphan*/  vm_page_insert (TYPE_1__*,struct vm_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mmap_gref(struct per_user_data *priv_user, struct gntdev_gref *gref_start,
    uint32_t count, vm_size_t size, struct vm_object **object)
{
	vm_object_t mem_obj;
	struct gntdev_gref *gref;

	mem_obj = vm_object_allocate(OBJT_PHYS, size);
	if (mem_obj == NULL)
		return (ENOMEM);

	mtx_lock(&priv_user->user_data_lock);
	VM_OBJECT_WLOCK(mem_obj);
	for (gref = gref_start; gref != NULL && count > 0; gref =
	    RB_NEXT(gref_tree_head, &priv_user->gref_tree, gref)) {
		if (gref->page->object)
			break;

		vm_page_insert(gref->page, mem_obj,
		    OFF_TO_IDX(gref->file_index));

		count--;
	}
	VM_OBJECT_WUNLOCK(mem_obj);
	mtx_unlock(&priv_user->user_data_lock);

	if (count) {
		vm_object_deallocate(mem_obj);
		return (EINVAL);
	}

	*object = mem_obj;

	return (0);

}