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
struct pci_device_id {int /*<<< orphan*/  driver_data; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 
 int i5400_probe1 (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_enable_device (struct pci_dev*) ; 

__attribute__((used)) static int i5400_init_one(struct pci_dev *pdev, const struct pci_device_id *id)
{
	int rc;

	edac_dbg(0, "MC:\n");

	/* wake up device */
	rc = pci_enable_device(pdev);
	if (rc)
		return rc;

	/* now probe and enable the device */
	return i5400_probe1(pdev, id->driver_data);
}