#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  vm_seglist; } ;
typedef  TYPE_1__ vmem_t ;
struct TYPE_9__ {scalar_t__ bt_type; } ;
typedef  TYPE_2__ bt_t ;

/* Variables and functions */
 scalar_t__ BT_TYPE_CURSOR ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_free (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  bt_seglist ; 

__attribute__((used)) static void
bt_remseg(vmem_t *vm, bt_t *bt)
{

	MPASS(bt->bt_type != BT_TYPE_CURSOR);
	TAILQ_REMOVE(&vm->vm_seglist, bt, bt_seglist);
	bt_free(vm, bt);
}