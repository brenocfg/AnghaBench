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
struct sta2x11_instance {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 struct sta2x11_instance* sta2x11_pdev_to_instance (struct pci_dev*) ; 

struct sta2x11_instance *sta2x11_get_instance(struct pci_dev *pdev)
{
	return sta2x11_pdev_to_instance(pdev);
}