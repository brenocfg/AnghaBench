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
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 struct ichwd_device* ichwd_smb_devices ; 
 int /*<<< orphan*/ * pci_find_dbsf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_get_domain (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static device_t
ichwd_find_smb_dev(device_t isa, struct ichwd_device **id_p)
{
	struct ichwd_device *id;
	device_t isab, smb;
	uint16_t devid;

	/*
	 * Check if SMBus controller provides TCO configuration.
	 * The controller's device and function are fixed and we expect
	 * it to be on the same bus as ISA bridge.
	 */
	isab = device_get_parent(isa);
	smb = pci_find_dbsf(pci_get_domain(isab), pci_get_bus(isab), 31, 4);
	if (smb == NULL)
		return (NULL);
	if (pci_get_vendor(smb) != VENDORID_INTEL)
		return (NULL);
	devid = pci_get_device(smb);
	for (id = ichwd_smb_devices; id->desc != NULL; ++id) {
		if (devid == id->device) {
			if (id_p != NULL)
				*id_p = id;
			return (smb);
		}
	}

	return (NULL);
}