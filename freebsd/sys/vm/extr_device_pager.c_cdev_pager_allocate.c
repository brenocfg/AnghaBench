#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  scalar_t__ vm_pindex_t ;
typedef  int vm_ooffset_t ;
typedef  TYPE_3__* vm_object_t ;
typedef  int /*<<< orphan*/  u_short ;
struct ucred {int dummy; } ;
struct cdev_pager_ops {scalar_t__ (* cdev_pg_ctor ) (void*,int,int /*<<< orphan*/ ,int,struct ucred*,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * cdev_pg_populate; } ;
typedef  enum obj_type { ____Placeholder_obj_type } obj_type ;
struct TYPE_10__ {struct cdev_pager_ops* ops; int /*<<< orphan*/  devp_pglist; void* dev; } ;
struct TYPE_11__ {TYPE_1__ devp; } ;
struct TYPE_12__ {scalar_t__ size; int type; struct TYPE_12__* handle; TYPE_2__ un_pager; int /*<<< orphan*/  pg_color; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int OBJT_DEVICE ; 
 int OBJT_MGTDEVICE ; 
 int /*<<< orphan*/  OBJ_COLORED ; 
 scalar_t__ OBJ_MAX_SIZE ; 
 int /*<<< orphan*/  OBJ_POPULATE ; 
 scalar_t__ OFF_TO_IDX (int) ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pager_mtx ; 
 int /*<<< orphan*/  dev_pager_object_list ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pager_object_list ; 
 int round_page (int) ; 
 scalar_t__ stub1 (void*,int,int /*<<< orphan*/ ,int,struct ucred*,int /*<<< orphan*/ *) ; 
 TYPE_3__* vm_object_allocate (int,scalar_t__) ; 
 int /*<<< orphan*/  vm_object_deallocate (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_object_set_flag (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* vm_pager_object_lookup (int /*<<< orphan*/ *,void*) ; 

vm_object_t
cdev_pager_allocate(void *handle, enum obj_type tp, struct cdev_pager_ops *ops,
    vm_ooffset_t size, vm_prot_t prot, vm_ooffset_t foff, struct ucred *cred)
{
	vm_object_t object, object1;
	vm_pindex_t pindex;
	u_short color;

	if (tp != OBJT_DEVICE && tp != OBJT_MGTDEVICE)
		return (NULL);
	KASSERT(tp == OBJT_MGTDEVICE || ops->cdev_pg_populate == NULL,
	    ("populate on unmanaged device pager"));

	/*
	 * Offset should be page aligned.
	 */
	if (foff & PAGE_MASK)
		return (NULL);

	/*
	 * Treat the mmap(2) file offset as an unsigned value for a
	 * device mapping.  This, in effect, allows a user to pass all
	 * possible off_t values as the mapping cookie to the driver.  At
	 * this point, we know that both foff and size are a multiple
	 * of the page size.  Do a check to avoid wrap.
	 */
	size = round_page(size);
	pindex = OFF_TO_IDX(foff) + OFF_TO_IDX(size);
	if (pindex > OBJ_MAX_SIZE || pindex < OFF_TO_IDX(foff) ||
	    pindex < OFF_TO_IDX(size))
		return (NULL);

	if (ops->cdev_pg_ctor(handle, size, prot, foff, cred, &color) != 0)
		return (NULL);
	mtx_lock(&dev_pager_mtx);

	/*
	 * Look up pager, creating as necessary.
	 */
	object1 = NULL;
	object = vm_pager_object_lookup(&dev_pager_object_list, handle);
	if (object == NULL) {
		/*
		 * Allocate object and associate it with the pager.  Initialize
		 * the object's pg_color based upon the physical address of the
		 * device's memory.
		 */
		mtx_unlock(&dev_pager_mtx);
		object1 = vm_object_allocate(tp, pindex);
		object1->flags |= OBJ_COLORED;
		object1->pg_color = color;
		object1->handle = handle;
		object1->un_pager.devp.ops = ops;
		object1->un_pager.devp.dev = handle;
		TAILQ_INIT(&object1->un_pager.devp.devp_pglist);
		mtx_lock(&dev_pager_mtx);
		object = vm_pager_object_lookup(&dev_pager_object_list, handle);
		if (object != NULL) {
			/*
			 * We raced with other thread while allocating object.
			 */
			if (pindex > object->size)
				object->size = pindex;
			KASSERT(object->type == tp,
			    ("Inconsistent device pager type %p %d",
			    object, tp));
			KASSERT(object->un_pager.devp.ops == ops,
			    ("Inconsistent devops %p %p", object, ops));
		} else {
			object = object1;
			object1 = NULL;
			object->handle = handle;
			TAILQ_INSERT_TAIL(&dev_pager_object_list, object,
			    pager_object_list);
			if (ops->cdev_pg_populate != NULL)
				vm_object_set_flag(object, OBJ_POPULATE);
		}
	} else {
		if (pindex > object->size)
			object->size = pindex;
		KASSERT(object->type == tp,
		    ("Inconsistent device pager type %p %d", object, tp));
	}
	mtx_unlock(&dev_pager_mtx);
	if (object1 != NULL) {
		object1->handle = object1;
		mtx_lock(&dev_pager_mtx);
		TAILQ_INSERT_TAIL(&dev_pager_object_list, object1,
		    pager_object_list);
		mtx_unlock(&dev_pager_mtx);
		vm_object_deallocate(object1);
	}
	return (object);
}