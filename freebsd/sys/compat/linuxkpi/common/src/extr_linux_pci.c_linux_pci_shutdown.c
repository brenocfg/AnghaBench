#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {TYPE_1__* pdrv; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* shutdown ) (struct pci_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  curthread ; 
 struct pci_dev* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_set_current (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*) ; 

__attribute__((used)) static int
linux_pci_shutdown(device_t dev)
{
	struct pci_dev *pdev;

	linux_set_current(curthread);
	pdev = device_get_softc(dev);
	if (pdev->pdrv->shutdown != NULL)
		pdev->pdrv->shutdown(pdev);
	return (0);
}