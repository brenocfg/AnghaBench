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
struct pci_dev {int dummy; } ;
struct agp_bridge_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  agp_put_bridge (struct agp_bridge_data*) ; 
 int /*<<< orphan*/  agp_remove_bridge (struct agp_bridge_data*) ; 
 struct agp_bridge_data* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void agp_intel_i460_remove(struct pci_dev *pdev)
{
	struct agp_bridge_data *bridge = pci_get_drvdata(pdev);

	agp_remove_bridge(bridge);
	agp_put_bridge(bridge);
}