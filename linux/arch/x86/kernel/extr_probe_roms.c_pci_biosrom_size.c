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
struct resource {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 struct resource* find_oprom (struct pci_dev*) ; 
 size_t resource_size (struct resource*) ; 

size_t pci_biosrom_size(struct pci_dev *pdev)
{
	struct resource *oprom = find_oprom(pdev);

	return oprom ? resource_size(oprom) : 0;
}