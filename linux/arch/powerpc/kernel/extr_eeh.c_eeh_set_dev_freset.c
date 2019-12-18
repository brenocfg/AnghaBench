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
struct pci_dev {unsigned int needs_freset; } ;
struct eeh_dev {int dummy; } ;

/* Variables and functions */
 struct pci_dev* eeh_dev_to_pci_dev (struct eeh_dev*) ; 

__attribute__((used)) static void eeh_set_dev_freset(struct eeh_dev *edev, void *flag)
{
	struct pci_dev *dev;
	unsigned int *freset = (unsigned int *)flag;

	dev = eeh_dev_to_pci_dev(edev);
	if (dev)
		*freset |= dev->needs_freset;
}