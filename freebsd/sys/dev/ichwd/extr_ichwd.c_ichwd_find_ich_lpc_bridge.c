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
typedef  scalar_t__ uint16_t ;
struct ichwd_device {scalar_t__ device; int /*<<< orphan*/ * desc; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 scalar_t__ VENDORID_INTEL ; 
 scalar_t__ devclass_find (char*) ; 
 scalar_t__ device_get_devclass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 struct ichwd_device* ichwd_devices ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static device_t
ichwd_find_ich_lpc_bridge(device_t isa, struct ichwd_device **id_p)
{
	struct ichwd_device *id;
	device_t isab, pci;
	uint16_t devid;

	/* Check whether parent ISA bridge looks familiar. */
	isab = device_get_parent(isa);
	pci = device_get_parent(isab);
	if (pci == NULL || device_get_devclass(pci) != devclass_find("pci"))
		return (NULL);
	if (pci_get_vendor(isab) != VENDORID_INTEL)
		return (NULL);
	devid = pci_get_device(isab);
	for (id = ichwd_devices; id->desc != NULL; ++id) {
		if (devid == id->device) {
			if (id_p != NULL)
				*id_p = id;
			return (isab);
		}
	}

	return (NULL);
}