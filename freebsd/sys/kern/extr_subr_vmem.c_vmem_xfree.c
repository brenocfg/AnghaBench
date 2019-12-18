#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {scalar_t__ vm_quantum_mask; } ;
typedef  TYPE_1__ vmem_t ;
typedef  int /*<<< orphan*/  vmem_size_t ;
typedef  scalar_t__ vmem_addr_t ;
struct TYPE_26__ {scalar_t__ bt_start; scalar_t__ bt_size; scalar_t__ bt_type; } ;
typedef  TYPE_2__ bt_t ;

/* Variables and functions */
 scalar_t__ BT_END (TYPE_2__*) ; 
 int /*<<< orphan*/  BT_MAXFREE ; 
 scalar_t__ BT_TYPE_BUSY ; 
 scalar_t__ BT_TYPE_FREE ; 
 int /*<<< orphan*/  MPASS (int) ; 
 TYPE_2__* TAILQ_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* TAILQ_PREV (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMEM_CONDVAR_BROADCAST (TYPE_1__*) ; 
 int /*<<< orphan*/  VMEM_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  bt_freetrim (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_insfree (TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__* bt_lookupbusy (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  bt_rembusy (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  bt_remfree (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  bt_remseg (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  bt_seglist ; 
 scalar_t__ vmem_roundup_size (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_seglist ; 
 int /*<<< orphan*/  vmem_try_release (TYPE_1__*,TYPE_2__*,int) ; 

void
vmem_xfree(vmem_t *vm, vmem_addr_t addr, vmem_size_t size)
{
	bt_t *bt;
	bt_t *t;

	MPASS(size > 0);

	VMEM_LOCK(vm);
	bt = bt_lookupbusy(vm, addr);
	MPASS(bt != NULL);
	MPASS(bt->bt_start == addr);
	MPASS(bt->bt_size == vmem_roundup_size(vm, size) ||
	    bt->bt_size - vmem_roundup_size(vm, size) <= vm->vm_quantum_mask);
	MPASS(bt->bt_type == BT_TYPE_BUSY);
	bt_rembusy(vm, bt);
	bt->bt_type = BT_TYPE_FREE;

	/* coalesce */
	t = TAILQ_NEXT(bt, bt_seglist);
	if (t != NULL && t->bt_type == BT_TYPE_FREE) {
		MPASS(BT_END(bt) < t->bt_start);	/* YYY */
		bt->bt_size += t->bt_size;
		bt_remfree(vm, t);
		bt_remseg(vm, t);
	}
	t = TAILQ_PREV(bt, vmem_seglist, bt_seglist);
	if (t != NULL && t->bt_type == BT_TYPE_FREE) {
		MPASS(BT_END(t) < bt->bt_start);	/* YYY */
		bt->bt_size += t->bt_size;
		bt->bt_start = t->bt_start;
		bt_remfree(vm, t);
		bt_remseg(vm, t);
	}

	if (!vmem_try_release(vm, bt, false)) {
		bt_insfree(vm, bt);
		VMEM_CONDVAR_BROADCAST(vm);
		bt_freetrim(vm, BT_MAXFREE);
	}
}