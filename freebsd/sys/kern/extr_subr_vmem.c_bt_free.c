#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  vm_nfreetags; int /*<<< orphan*/  vm_freetags; } ;
typedef  TYPE_1__ vmem_t ;
typedef  int /*<<< orphan*/  bt_t ;

/* Variables and functions */
 int /*<<< orphan*/ * LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  VMEM_ASSERT_LOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  bt_freelist ; 

__attribute__((used)) static inline void
bt_free(vmem_t *vm, bt_t *bt)
{

	VMEM_ASSERT_LOCKED(vm);
	MPASS(LIST_FIRST(&vm->vm_freetags) != bt);
	LIST_INSERT_HEAD(&vm->vm_freetags, bt, bt_freelist);
	vm->vm_nfreetags++;
}