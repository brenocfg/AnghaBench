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
typedef  TYPE_1__* vm_object_t ;
struct TYPE_6__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJT_DEAD ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pager_object_list ; 
 int /*<<< orphan*/  phys_pager_mtx ; 
 int /*<<< orphan*/  phys_pager_object_list ; 

__attribute__((used)) static void
phys_pager_dealloc(vm_object_t object)
{

	if (object->handle != NULL) {
		VM_OBJECT_WUNLOCK(object);
		mtx_lock(&phys_pager_mtx);
		TAILQ_REMOVE(&phys_pager_object_list, object, pager_object_list);
		mtx_unlock(&phys_pager_mtx);
		VM_OBJECT_WLOCK(object);
	}
	object->handle = NULL;
	object->type = OBJT_DEAD;
}