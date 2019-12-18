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
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ PCI_DOMAINMAX ; 
 int PCI_RES_BUS ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int pci_domain_adjust_bus (scalar_t__,int /*<<< orphan*/ ,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pcib_adjust_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vmd_adjust_resource(device_t dev, device_t child, int type,
    struct resource *r, rman_res_t start, rman_res_t end)
{
	struct resource *res = r;

	if (type == PCI_RES_BUS)
		return (pci_domain_adjust_bus(PCI_DOMAINMAX -
			device_get_unit(dev), child, res, start, end));
	return (pcib_adjust_resource(dev, child, type, res, start, end));
}