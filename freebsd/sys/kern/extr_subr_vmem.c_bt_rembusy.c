#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ vm_nbusytag; int /*<<< orphan*/  vm_inuse; } ;
typedef  TYPE_1__ vmem_t ;
struct TYPE_8__ {scalar_t__ bt_size; } ;
typedef  TYPE_2__ bt_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  VMEM_ASSERT_LOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  bt_hashlist ; 

__attribute__((used)) static void
bt_rembusy(vmem_t *vm, bt_t *bt)
{

	VMEM_ASSERT_LOCKED(vm);
	MPASS(vm->vm_nbusytag > 0);
	vm->vm_inuse -= bt->bt_size;
	vm->vm_nbusytag--;
	LIST_REMOVE(bt, bt_hashlist);
}