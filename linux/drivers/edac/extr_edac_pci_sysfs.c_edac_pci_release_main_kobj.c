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
struct kobject {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct kobject*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void edac_pci_release_main_kobj(struct kobject *kobj)
{
	edac_dbg(0, "here to module_put(THIS_MODULE)\n");

	kfree(kobj);

	/* last reference to top EDAC PCI kobject has been removed,
	 * NOW release our ref count on the core module
	 */
	module_put(THIS_MODULE);
}