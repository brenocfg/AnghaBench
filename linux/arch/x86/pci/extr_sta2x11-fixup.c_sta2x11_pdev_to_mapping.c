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
struct sta2x11_mapping {int dummy; } ;
struct sta2x11_instance {struct sta2x11_mapping* map; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int sta2x11_pdev_to_ep (struct pci_dev*) ; 
 struct sta2x11_instance* sta2x11_pdev_to_instance (struct pci_dev*) ; 

__attribute__((used)) static struct sta2x11_mapping *sta2x11_pdev_to_mapping(struct pci_dev *pdev)
{
	struct sta2x11_instance *instance;
	int ep;

	instance = sta2x11_pdev_to_instance(pdev);
	if (!instance)
		return NULL;
	ep = sta2x11_pdev_to_ep(pdev);
	return instance->map + ep;
}