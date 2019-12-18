#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 TYPE_2__ linux_class_misc ; 
 int /*<<< orphan*/  linux_class_root ; 
 int /*<<< orphan*/  linux_kobject_kfree_name (int /*<<< orphan*/ *) ; 
 TYPE_1__ linux_root_device ; 
 int /*<<< orphan*/  linux_vma_lock ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_lock ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmmaplock ; 

__attribute__((used)) static void
linux_compat_uninit(void *arg)
{
	linux_kobject_kfree_name(&linux_class_root);
	linux_kobject_kfree_name(&linux_root_device.kobj);
	linux_kobject_kfree_name(&linux_class_misc.kobj);

	mtx_destroy(&vmmaplock);
	spin_lock_destroy(&pci_lock);
	rw_destroy(&linux_vma_lock);
}