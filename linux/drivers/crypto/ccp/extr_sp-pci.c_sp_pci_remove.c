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
struct sp_device {int dummy; } ;
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;

/* Variables and functions */
 struct sp_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sp_destroy (struct sp_device*) ; 
 int /*<<< orphan*/  sp_free_irqs (struct sp_device*) ; 

__attribute__((used)) static void sp_pci_remove(struct pci_dev *pdev)
{
	struct device *dev = &pdev->dev;
	struct sp_device *sp = dev_get_drvdata(dev);

	if (!sp)
		return;

	sp_destroy(sp);

	sp_free_irqs(sp);
}