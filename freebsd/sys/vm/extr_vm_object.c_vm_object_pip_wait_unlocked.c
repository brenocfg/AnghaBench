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
typedef  TYPE_1__* vm_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  paging_in_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVM ; 
 scalar_t__ REFCOUNT_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_UNLOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  refcount_wait (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void
vm_object_pip_wait_unlocked(vm_object_t object, char *waitid)
{

	VM_OBJECT_ASSERT_UNLOCKED(object);

	while (REFCOUNT_COUNT(object->paging_in_progress) > 0)
		refcount_wait(&object->paging_in_progress, waitid, PVM);
}