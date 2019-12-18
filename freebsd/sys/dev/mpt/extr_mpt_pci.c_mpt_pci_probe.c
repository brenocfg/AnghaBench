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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int BUS_PROBE_LOW_PRIORITY ; 
 int ENXIO ; 
#define  MPI_MANUFACTPAGE_DEVICEID_FC909 152 
#define  MPI_MANUFACTPAGE_DEVICEID_FC909_FB 151 
#define  MPI_MANUFACTPAGE_DEVICEID_FC919 150 
#define  MPI_MANUFACTPAGE_DEVICEID_FC919X 149 
#define  MPI_MANUFACTPAGE_DEVICEID_FC919X_LAN_FB 148 
#define  MPI_MANUFACTPAGE_DEVICEID_FC919_LAN_FB 147 
#define  MPI_MANUFACTPAGE_DEVICEID_FC929 146 
#define  MPI_MANUFACTPAGE_DEVICEID_FC929X 145 
#define  MPI_MANUFACTPAGE_DEVICEID_FC929X_LAN_FB 144 
#define  MPI_MANUFACTPAGE_DEVICEID_FC929_LAN_FB 143 
#define  MPI_MANUFACTPAGE_DEVICEID_FC949E 142 
#define  MPI_MANUFACTPAGE_DEVICEID_FC949X 141 
#define  MPI_MANUFACTPAGE_DEVID_53C1030 140 
#define  MPI_MANUFACTPAGE_DEVID_53C1030ZC 139 
#define  MPI_MANUFACTPAGE_DEVID_SAS1064 138 
#define  MPI_MANUFACTPAGE_DEVID_SAS1064A 137 
#define  MPI_MANUFACTPAGE_DEVID_SAS1064E 136 
#define  MPI_MANUFACTPAGE_DEVID_SAS1066 135 
#define  MPI_MANUFACTPAGE_DEVID_SAS1066E 134 
#define  MPI_MANUFACTPAGE_DEVID_SAS1068 133 
#define  MPI_MANUFACTPAGE_DEVID_SAS1068A_FB 132 
#define  MPI_MANUFACTPAGE_DEVID_SAS1068E 131 
#define  MPI_MANUFACTPAGE_DEVID_SAS1068E_FB 130 
#define  MPI_MANUFACTPAGE_DEVID_SAS1078 129 
#define  MPI_MANUFACTPAGE_DEVID_SAS1078DE_FB 128 
 scalar_t__ MPI_MANUFACTPAGE_VENDORID_LSILOGIC ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char const*) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpt_pci_probe(device_t dev)
{
	const char *desc;
	int rval;

	if (pci_get_vendor(dev) != MPI_MANUFACTPAGE_VENDORID_LSILOGIC)
		return (ENXIO);

	rval = BUS_PROBE_DEFAULT;
	switch (pci_get_device(dev)) {
	case MPI_MANUFACTPAGE_DEVICEID_FC909_FB:
		desc = "LSILogic FC909 FC Adapter";
		break;
	case MPI_MANUFACTPAGE_DEVICEID_FC909:
		desc = "LSILogic FC909A FC Adapter";
		break;
	case MPI_MANUFACTPAGE_DEVICEID_FC919:
		desc = "LSILogic FC919 FC Adapter";
		break;
	case MPI_MANUFACTPAGE_DEVICEID_FC919_LAN_FB:
		desc = "LSILogic FC919 LAN Adapter";
		break;
	case MPI_MANUFACTPAGE_DEVICEID_FC929:
		desc = "Dual LSILogic FC929 FC Adapter";
		break;
	case MPI_MANUFACTPAGE_DEVICEID_FC929_LAN_FB:
		desc = "Dual LSILogic FC929 LAN Adapter";
		break;
	case MPI_MANUFACTPAGE_DEVICEID_FC919X:
		desc = "LSILogic FC919 FC PCI-X Adapter";
		break;
	case MPI_MANUFACTPAGE_DEVICEID_FC919X_LAN_FB:
		desc = "LSILogic FC919 LAN PCI-X Adapter";
		break;
	case MPI_MANUFACTPAGE_DEVICEID_FC929X:
		desc = "Dual LSILogic FC929X 2Gb/s FC PCI-X Adapter";
		break;
	case MPI_MANUFACTPAGE_DEVICEID_FC929X_LAN_FB:
		desc = "Dual LSILogic FC929X LAN PCI-X Adapter";
		break;
	case MPI_MANUFACTPAGE_DEVICEID_FC949E:
		desc = "Dual LSILogic FC7X04X 4Gb/s FC PCI-Express Adapter";
		break;
	case MPI_MANUFACTPAGE_DEVICEID_FC949X:
		desc = "Dual LSILogic FC7X04X 4Gb/s FC PCI-X Adapter";
		break;
	case MPI_MANUFACTPAGE_DEVID_53C1030:
	case MPI_MANUFACTPAGE_DEVID_53C1030ZC:
		desc = "LSILogic 1030 Ultra4 Adapter";
		break;
	case MPI_MANUFACTPAGE_DEVID_SAS1068E_FB:
		/*
		 * Allow mfi(4) to claim this device in case it's in MegaRAID
		 * mode.
		 */
		rval = BUS_PROBE_LOW_PRIORITY;
		/* FALLTHROUGH */
	case MPI_MANUFACTPAGE_DEVID_SAS1064:
	case MPI_MANUFACTPAGE_DEVID_SAS1064A:
	case MPI_MANUFACTPAGE_DEVID_SAS1064E:
	case MPI_MANUFACTPAGE_DEVID_SAS1066:
	case MPI_MANUFACTPAGE_DEVID_SAS1066E:
	case MPI_MANUFACTPAGE_DEVID_SAS1068:
	case MPI_MANUFACTPAGE_DEVID_SAS1068A_FB:
	case MPI_MANUFACTPAGE_DEVID_SAS1068E:
	case MPI_MANUFACTPAGE_DEVID_SAS1078:
	case MPI_MANUFACTPAGE_DEVID_SAS1078DE_FB:
		desc = "LSILogic SAS/SATA Adapter";
		break;
	default:
		return (ENXIO);
	}

	device_set_desc(dev, desc);
	return (rval);
}