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
typedef  scalar_t__ u_int16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
#define  NFSMB_DEVICEID_NF2_SMB 141 
#define  NFSMB_DEVICEID_NF2_ULTRA_SMB 140 
#define  NFSMB_DEVICEID_NF3_250GB_SMB 139 
#define  NFSMB_DEVICEID_NF3_PRO150_SMB 138 
#define  NFSMB_DEVICEID_NF4_04_SMB 137 
#define  NFSMB_DEVICEID_NF4_51_SMB 136 
#define  NFSMB_DEVICEID_NF4_55_SMB 135 
#define  NFSMB_DEVICEID_NF4_61_SMB 134 
#define  NFSMB_DEVICEID_NF4_65_SMB 133 
#define  NFSMB_DEVICEID_NF4_67_SMB 132 
#define  NFSMB_DEVICEID_NF4_73_SMB 131 
#define  NFSMB_DEVICEID_NF4_78S_SMB 130 
#define  NFSMB_DEVICEID_NF4_79_SMB 129 
#define  NFSMB_DEVICEID_NF4_SMB 128 
 scalar_t__ NFSMB_VENDORID_NVIDIA ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfsmb_probe(device_t dev)
{
	u_int16_t vid;
	u_int16_t did;

	vid = pci_get_vendor(dev);
	did = pci_get_device(dev);

	if (vid == NFSMB_VENDORID_NVIDIA) {
		switch(did) {
		case NFSMB_DEVICEID_NF2_SMB:
		case NFSMB_DEVICEID_NF2_ULTRA_SMB:
		case NFSMB_DEVICEID_NF3_PRO150_SMB:
		case NFSMB_DEVICEID_NF3_250GB_SMB:
		case NFSMB_DEVICEID_NF4_SMB:
		case NFSMB_DEVICEID_NF4_04_SMB:
		case NFSMB_DEVICEID_NF4_51_SMB:
		case NFSMB_DEVICEID_NF4_55_SMB:
		case NFSMB_DEVICEID_NF4_61_SMB:
		case NFSMB_DEVICEID_NF4_65_SMB:
		case NFSMB_DEVICEID_NF4_67_SMB:
		case NFSMB_DEVICEID_NF4_73_SMB:
		case NFSMB_DEVICEID_NF4_78S_SMB:
		case NFSMB_DEVICEID_NF4_79_SMB:
			device_set_desc(dev, "nForce2/3/4 MCP SMBus Controller");
			return (BUS_PROBE_DEFAULT);
		}
	}

	return (ENXIO);
}