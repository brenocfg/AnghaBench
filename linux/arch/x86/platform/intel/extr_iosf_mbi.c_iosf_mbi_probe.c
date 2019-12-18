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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iosf_mbi_sem_address ; 
 int /*<<< orphan*/  mbi_pdev ; 
 int /*<<< orphan*/  pci_dev_get (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 

__attribute__((used)) static int iosf_mbi_probe(struct pci_dev *pdev,
			  const struct pci_device_id *dev_id)
{
	int ret;

	ret = pci_enable_device(pdev);
	if (ret < 0) {
		dev_err(&pdev->dev, "error: could not enable device\n");
		return ret;
	}

	mbi_pdev = pci_dev_get(pdev);
	iosf_mbi_sem_address = dev_id->driver_data;

	return 0;
}