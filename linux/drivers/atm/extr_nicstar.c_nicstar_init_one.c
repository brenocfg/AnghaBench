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
struct pci_device_id {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/ ** cards ; 
 unsigned int ns_init_card (int,struct pci_dev*) ; 

__attribute__((used)) static int nicstar_init_one(struct pci_dev *pcidev,
			    const struct pci_device_id *ent)
{
	static int index = -1;
	unsigned int error;

	index++;
	cards[index] = NULL;

	error = ns_init_card(index, pcidev);
	if (error) {
		cards[index--] = NULL;	/* don't increment index */
		goto err_out;
	}

	return 0;
err_out:
	return -ENODEV;
}