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
 int /*<<< orphan*/  dev_pager_mtx ; 
 int /*<<< orphan*/  dev_pager_object_list ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_pager_object_lookup (int /*<<< orphan*/ *,void*) ; 

vm_object_t
cdev_pager_lookup(void *handle)
{
	vm_object_t object;

	mtx_lock(&dev_pager_mtx);
	object = vm_pager_object_lookup(&dev_pager_object_list, handle);
	mtx_unlock(&dev_pager_mtx);
	return (object);
}