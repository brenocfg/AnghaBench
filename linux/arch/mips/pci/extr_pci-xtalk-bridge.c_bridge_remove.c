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
struct platform_device {int dummy; } ;
struct pci_bus {int dummy; } ;
struct bridge_controller {int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 struct bridge_controller* BRIDGE_CONTROLLER (struct pci_bus*) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_lock_rescan_remove () ; 
 int /*<<< orphan*/  pci_remove_root_bus (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_stop_root_bus (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_unlock_rescan_remove () ; 
 struct pci_bus* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int bridge_remove(struct platform_device *pdev)
{
	struct pci_bus *bus = platform_get_drvdata(pdev);
	struct bridge_controller *bc = BRIDGE_CONTROLLER(bus);

	irq_domain_remove(bc->domain);
	pci_lock_rescan_remove();
	pci_stop_root_bus(bus);
	pci_remove_root_bus(bus);
	pci_unlock_rescan_remove();

	return 0;
}