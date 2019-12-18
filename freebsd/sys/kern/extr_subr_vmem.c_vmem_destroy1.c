#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ vm_nbusytag; int /*<<< orphan*/ * vm_hashlist; int /*<<< orphan*/ * vm_hash0; int /*<<< orphan*/  vm_seglist; int /*<<< orphan*/  vm_cursor; } ;
typedef  TYPE_1__ vmem_t ;
typedef  int /*<<< orphan*/  bt_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_VMEM ; 
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMEM_CONDVAR_DESTROY (TYPE_1__*) ; 
 int /*<<< orphan*/  VMEM_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  VMEM_LOCK_DESTROY (TYPE_1__*) ; 
 int /*<<< orphan*/  bt_freetrim (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_remseg (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_seglist ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qc_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vmem_zone ; 

__attribute__((used)) static void
vmem_destroy1(vmem_t *vm)
{
	bt_t *bt;

	/*
	 * Drain per-cpu quantum caches.
	 */
	qc_destroy(vm);

	/*
	 * The vmem should now only contain empty segments.
	 */
	VMEM_LOCK(vm);
	MPASS(vm->vm_nbusytag == 0);

	TAILQ_REMOVE(&vm->vm_seglist, &vm->vm_cursor, bt_seglist);
	while ((bt = TAILQ_FIRST(&vm->vm_seglist)) != NULL)
		bt_remseg(vm, bt);

	if (vm->vm_hashlist != NULL && vm->vm_hashlist != vm->vm_hash0)
		free(vm->vm_hashlist, M_VMEM);

	bt_freetrim(vm, 0);

	VMEM_CONDVAR_DESTROY(vm);
	VMEM_LOCK_DESTROY(vm);
	uma_zfree(vmem_zone, vm);
}