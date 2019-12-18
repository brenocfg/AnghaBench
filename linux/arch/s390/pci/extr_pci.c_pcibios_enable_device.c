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
struct zpci_dev {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int pci_enable_resources (struct pci_dev*,int) ; 
 struct zpci_dev* to_zpci (struct pci_dev*) ; 
 int /*<<< orphan*/  zpci_debug_init_device (struct zpci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpci_fmb_enable_device (struct zpci_dev*) ; 

int pcibios_enable_device(struct pci_dev *pdev, int mask)
{
	struct zpci_dev *zdev = to_zpci(pdev);

	zpci_debug_init_device(zdev, dev_name(&pdev->dev));
	zpci_fmb_enable_device(zdev);

	return pci_enable_resources(pdev, mask);
}