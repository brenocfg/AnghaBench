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
struct pci_bus {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __of_scan_bus (struct device_node*,struct pci_bus*,int /*<<< orphan*/ ) ; 

void of_scan_bus(struct device_node *node, struct pci_bus *bus)
{
	__of_scan_bus(node, bus, 0);
}