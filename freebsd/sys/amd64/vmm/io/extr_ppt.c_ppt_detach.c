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
struct pptdev {int /*<<< orphan*/ * vm; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pptdev*,int /*<<< orphan*/ ) ; 
 struct pptdev* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_add_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_host_domain () ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  num_pptdevs ; 
 int /*<<< orphan*/  pci_disable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_rid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pptdev_list ; 

__attribute__((used)) static int
ppt_detach(device_t dev)
{
	struct pptdev *ppt;

	ppt = device_get_softc(dev);

	if (ppt->vm != NULL)
		return (EBUSY);
	num_pptdevs--;
	TAILQ_REMOVE(&pptdev_list, ppt, next);
	pci_disable_busmaster(dev);
	iommu_add_device(iommu_host_domain(), pci_get_rid(dev));

	return (0);
}