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
struct TYPE_4__ {int /*<<< orphan*/  busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_OBJECT_ASSERT_LOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_thread_fence_acq_rel () ; 
 int /*<<< orphan*/  refcount_acquire (int /*<<< orphan*/ *) ; 

void
vm_object_busy(vm_object_t obj)
{

	VM_OBJECT_ASSERT_LOCKED(obj);

	refcount_acquire(&obj->busy);
	/* The fence is required to order loads of page busy. */
	atomic_thread_fence_acq_rel();
}