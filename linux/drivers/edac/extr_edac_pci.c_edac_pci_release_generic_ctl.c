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
struct edac_pci_ctl_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  mod_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_pci_del_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_pci_free_ctl_info (struct edac_pci_ctl_info*) ; 

void edac_pci_release_generic_ctl(struct edac_pci_ctl_info *pci)
{
	edac_dbg(0, "pci mod=%s\n", pci->mod_name);

	edac_pci_del_device(pci->dev);
	edac_pci_free_ctl_info(pci);
}