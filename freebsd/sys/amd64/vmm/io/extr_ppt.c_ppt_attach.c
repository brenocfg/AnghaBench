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
struct pptdev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pptdev*,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 struct pptdev* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iommu_host_domain () ; 
 int /*<<< orphan*/  iommu_remove_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  num_pptdevs ; 
 int /*<<< orphan*/  pci_get_rid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pptdev_list ; 

__attribute__((used)) static int
ppt_attach(device_t dev)
{
	struct pptdev *ppt;

	ppt = device_get_softc(dev);

	iommu_remove_device(iommu_host_domain(), pci_get_rid(dev));
	num_pptdevs++;
	TAILQ_INSERT_TAIL(&pptdev_list, ppt, next);
	ppt->dev = dev;

	if (bootverbose)
		device_printf(dev, "attached\n");

	return (0);
}