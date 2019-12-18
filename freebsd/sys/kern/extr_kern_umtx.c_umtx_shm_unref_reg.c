#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_object_t ;
struct umtx_shm_reg {TYPE_1__* ushm_obj; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {TYPE_2__* shm_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_UMTXDEAD ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtx_shm_free_reg (struct umtx_shm_reg*) ; 
 int /*<<< orphan*/  umtx_shm_lock ; 
 int umtx_shm_unref_reg_locked (struct umtx_shm_reg*,int) ; 

__attribute__((used)) static void
umtx_shm_unref_reg(struct umtx_shm_reg *reg, bool force)
{
	vm_object_t object;
	bool dofree;

	if (force) {
		object = reg->ushm_obj->shm_object;
		VM_OBJECT_WLOCK(object);
		object->flags |= OBJ_UMTXDEAD;
		VM_OBJECT_WUNLOCK(object);
	}
	mtx_lock(&umtx_shm_lock);
	dofree = umtx_shm_unref_reg_locked(reg, force);
	mtx_unlock(&umtx_shm_lock);
	if (dofree)
		umtx_shm_free_reg(reg);
}