#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  vm_arg; int /*<<< orphan*/  (* vm_releasefn ) (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ;int /*<<< orphan*/  vm_size; } ;
typedef  TYPE_1__ vmem_t ;
typedef  scalar_t__ vmem_size_t ;
typedef  scalar_t__ vmem_addr_t ;
struct vmem_btag {scalar_t__ bt_type; scalar_t__ bt_size; scalar_t__ bt_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MAXFREE ; 
 scalar_t__ BT_TYPE_FREE ; 
 scalar_t__ BT_TYPE_SPAN ; 
 int /*<<< orphan*/  MPASS (int) ; 
 struct vmem_btag* TAILQ_PREV (struct vmem_btag*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMEM_CONDVAR_BROADCAST (TYPE_1__*) ; 
 int /*<<< orphan*/  bt_freetrim (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_remfree (TYPE_1__*,struct vmem_btag*) ; 
 int /*<<< orphan*/  bt_remseg (TYPE_1__*,struct vmem_btag*) ; 
 int /*<<< orphan*/  bt_seglist ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vmem_seglist ; 

__attribute__((used)) static int
vmem_try_release(vmem_t *vm, struct vmem_btag *bt, const bool remfree)
{
	struct vmem_btag *prev;

	MPASS(bt->bt_type == BT_TYPE_FREE);

	if (vm->vm_releasefn == NULL)
		return (0);

	prev = TAILQ_PREV(bt, vmem_seglist, bt_seglist);
	MPASS(prev != NULL);
	MPASS(prev->bt_type != BT_TYPE_FREE);

	if (prev->bt_type == BT_TYPE_SPAN && prev->bt_size == bt->bt_size) {
		vmem_addr_t spanaddr;
		vmem_size_t spansize;

		MPASS(prev->bt_start == bt->bt_start);
		spanaddr = prev->bt_start;
		spansize = prev->bt_size;
		if (remfree)
			bt_remfree(vm, bt);
		bt_remseg(vm, bt);
		bt_remseg(vm, prev);
		vm->vm_size -= spansize;
		VMEM_CONDVAR_BROADCAST(vm);
		bt_freetrim(vm, BT_MAXFREE);
		vm->vm_releasefn(vm->vm_arg, spanaddr, spansize);
		return (1);
	}
	return (0);
}