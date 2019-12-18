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
struct edac_pci_ctl_info {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void edac_pci_unregister_sysfs_instance_kobj(
			struct edac_pci_ctl_info *pci)
{
	edac_dbg(0, "\n");

	/* Unregister the instance kobject and allow its release
	 * function release the main reference count and then
	 * kfree the memory
	 */
	kobject_put(&pci->kobj);
}