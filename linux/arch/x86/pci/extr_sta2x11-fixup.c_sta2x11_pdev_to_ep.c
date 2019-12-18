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
struct sta2x11_instance {int bus0; } ;
struct pci_dev {TYPE_1__* bus; } ;
struct TYPE_2__ {int number; } ;

/* Variables and functions */
 struct sta2x11_instance* sta2x11_pdev_to_instance (struct pci_dev*) ; 

__attribute__((used)) static int sta2x11_pdev_to_ep(struct pci_dev *pdev)
{
	struct sta2x11_instance *instance;

	instance = sta2x11_pdev_to_instance(pdev);
	if (!instance)
		return -1;

	return pdev->bus->number - instance->bus0;
}