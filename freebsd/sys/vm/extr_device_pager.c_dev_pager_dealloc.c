#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  TYPE_4__* vm_object_t ;
struct TYPE_12__ {int /*<<< orphan*/  devp_pglist; int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct TYPE_11__ {TYPE_3__ devp; } ;
struct TYPE_13__ {scalar_t__ type; int /*<<< orphan*/ * handle; TYPE_2__ un_pager; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* cdev_pg_dtor ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ OBJT_DEAD ; 
 scalar_t__ OBJT_DEVICE ; 
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  dev_pager_free_page (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_pager_mtx ; 
 int /*<<< orphan*/  dev_pager_object_list ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pager_object_list ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dev_pager_dealloc(vm_object_t object)
{
	vm_page_t m;

	VM_OBJECT_WUNLOCK(object);
	object->un_pager.devp.ops->cdev_pg_dtor(object->un_pager.devp.dev);

	mtx_lock(&dev_pager_mtx);
	TAILQ_REMOVE(&dev_pager_object_list, object, pager_object_list);
	mtx_unlock(&dev_pager_mtx);
	VM_OBJECT_WLOCK(object);

	if (object->type == OBJT_DEVICE) {
		/*
		 * Free up our fake pages.
		 */
		while ((m = TAILQ_FIRST(&object->un_pager.devp.devp_pglist))
		    != NULL)
			dev_pager_free_page(object, m);
	}
	object->handle = NULL;
	object->type = OBJT_DEAD;
}