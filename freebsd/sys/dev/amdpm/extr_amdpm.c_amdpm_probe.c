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
typedef  int u_long ;
typedef  scalar_t__ u_int16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMDPCI_PMBASE ; 
 scalar_t__ AMDPM_DEVICEID_AMD756PM ; 
 scalar_t__ AMDPM_DEVICEID_AMD766PM ; 
 scalar_t__ AMDPM_DEVICEID_AMD768PM ; 
 scalar_t__ AMDPM_DEVICEID_AMD8111PM ; 
 scalar_t__ AMDPM_DEVICEID_NF_SMB ; 
 scalar_t__ AMDPM_VENDORID_AMD ; 
 scalar_t__ AMDPM_VENDORID_NVIDIA ; 
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  NFPCI_PMBASE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
amdpm_probe(device_t dev)
{
	u_long base;
	u_int16_t vid;
	u_int16_t did;

	vid = pci_get_vendor(dev);
	did = pci_get_device(dev);
	if ((vid == AMDPM_VENDORID_AMD) &&
	    ((did == AMDPM_DEVICEID_AMD756PM) ||
	     (did == AMDPM_DEVICEID_AMD766PM) ||
	     (did == AMDPM_DEVICEID_AMD768PM) ||
	     (did == AMDPM_DEVICEID_AMD8111PM))) {
		device_set_desc(dev, "AMD 756/766/768/8111 Power Management Controller");

		/* 
		 * We have to do this, since the BIOS won't give us the
		 * resource info (not mine, anyway).
		 */
		base = pci_read_config(dev, AMDPCI_PMBASE, 4);
		base &= 0xff00;
		bus_set_resource(dev, SYS_RES_IOPORT, AMDPCI_PMBASE,
				 base+0xe0, 32);
		return (BUS_PROBE_DEFAULT);
	}

	if ((vid == AMDPM_VENDORID_NVIDIA) &&
	    (did == AMDPM_DEVICEID_NF_SMB)) {
		device_set_desc(dev, "nForce SMBus Controller");

		/* 
		* We have to do this, since the BIOS won't give us the
		* resource info (not mine, anyway).
		*/
		base = pci_read_config(dev, NFPCI_PMBASE, 4);
		base &= 0xff00;
		bus_set_resource(dev, SYS_RES_IOPORT, NFPCI_PMBASE,
				 base, 32);

		return (BUS_PROBE_DEFAULT);
	}

	return ENXIO;
}