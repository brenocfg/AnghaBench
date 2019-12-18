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
struct pci_devinfo {int /*<<< orphan*/  cfg; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 scalar_t__ PCIR_IS_BIOS (int /*<<< orphan*/ *,int) ; 
 int SYS_RES_MEMORY ; 
 int bus_generic_deactivate_resource (scalar_t__,scalar_t__,int,int,struct resource*) ; 
 struct pci_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 int /*<<< orphan*/  pci_find_bar (scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_bar (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_start (struct resource*) ; 

int
pci_deactivate_resource(device_t dev, device_t child, int type,
    int rid, struct resource *r)
{
	struct pci_devinfo *dinfo;
	int error;

	error = bus_generic_deactivate_resource(dev, child, type, rid, r);
	if (error)
		return (error);

	/* Disable decoding for device ROMs. */
	if (device_get_parent(child) == dev) {
		dinfo = device_get_ivars(child);
		if (type == SYS_RES_MEMORY && PCIR_IS_BIOS(&dinfo->cfg, rid))
			pci_write_bar(child, pci_find_bar(child, rid),
			    rman_get_start(r));
	}
	return (0);
}