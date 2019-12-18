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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int nitrox_sriov_disable (struct pci_dev*) ; 
 int nitrox_sriov_enable (struct pci_dev*,int) ; 

int nitrox_sriov_configure(struct pci_dev *pdev, int num_vfs)
{
	if (!num_vfs)
		return nitrox_sriov_disable(pdev);

	return nitrox_sriov_enable(pdev, num_vfs);
}