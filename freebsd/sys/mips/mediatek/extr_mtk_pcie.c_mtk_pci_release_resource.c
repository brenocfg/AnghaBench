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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCI_RES_BUS ; 
 int bus_generic_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int pci_domain_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 

__attribute__((used)) static int
mtk_pci_release_resource(device_t bus, device_t child, int type, int rid,
    struct resource *res)
{

	if (type == PCI_RES_BUS)
		return (pci_domain_release_bus(0, child, rid, res));

	return (bus_generic_release_resource(bus, child, type, rid, res));
}