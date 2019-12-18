#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vm_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (int /*<<< orphan*/ ) ; 

void
zfs_vmobject_assert_wlocked(vm_object_t object)
{

	/*
	 * This is not ideal because FILE/LINE used by assertions will not
	 * be too helpful, but it must be an hard function for
	 * compatibility reasons.
	 */
	VM_OBJECT_ASSERT_WLOCKED(object);
}