#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pcie_location; scalar_t__ pcie_type; } ;
struct TYPE_4__ {TYPE_1__ pcie; } ;
struct pci_devinfo {TYPE_2__ cfg; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ PCIEM_TYPE_DOWNSTREAM_PORT ; 
 scalar_t__ PCIEM_TYPE_ROOT_PORT ; 
 int /*<<< orphan*/  bus_helper_reset_post (int /*<<< orphan*/ *,int) ; 
 int bus_helper_reset_prepare (int /*<<< orphan*/ *,int) ; 
 scalar_t__ devclass_find (char*) ; 
 scalar_t__ device_get_devclass (int /*<<< orphan*/ *) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 int pcie_link_reset (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
pcib_reset_child(device_t dev, device_t child, int flags)
{
	struct pci_devinfo *pdinfo;
	int error;

	error = 0;
	if (dev == NULL || device_get_parent(child) != dev)
		goto out;
	error = ENXIO;
	if (device_get_devclass(child) != devclass_find("pci"))
		goto out;
	pdinfo = device_get_ivars(dev);
	if (pdinfo->cfg.pcie.pcie_location != 0 &&
	    (pdinfo->cfg.pcie.pcie_type == PCIEM_TYPE_DOWNSTREAM_PORT ||
	    pdinfo->cfg.pcie.pcie_type == PCIEM_TYPE_ROOT_PORT)) {
		error = bus_helper_reset_prepare(child, flags);
		if (error == 0) {
			error = pcie_link_reset(dev,
			    pdinfo->cfg.pcie.pcie_location);
			/* XXXKIB call _post even if error != 0 ? */
			bus_helper_reset_post(child, flags);
		}
	}
out:
	return (error);
}