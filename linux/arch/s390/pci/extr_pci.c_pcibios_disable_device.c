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
struct zpci_dev {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 struct zpci_dev* to_zpci (struct pci_dev*) ; 
 int /*<<< orphan*/  zpci_debug_exit_device (struct zpci_dev*) ; 
 int /*<<< orphan*/  zpci_fmb_disable_device (struct zpci_dev*) ; 

void pcibios_disable_device(struct pci_dev *pdev)
{
	struct zpci_dev *zdev = to_zpci(pdev);

	zpci_fmb_disable_device(zdev);
	zpci_debug_exit_device(zdev);
}