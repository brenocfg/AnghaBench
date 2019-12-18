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
typedef  int uint32_t ;
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  ATA_SCONTROL 130 
 int ATA_SC_DET_DISABLE ; 
 int ATA_SC_DET_RESET ; 
 int ATA_SC_IPM_DIS_PARTIAL ; 
 int ATA_SC_IPM_DIS_SLUMBER ; 
#define  ATA_SERROR 129 
#define  ATA_SSTATUS 128 
 int ATA_SS_DET_NO_DEVICE ; 
 int ATA_SS_IPM_ACTIVE ; 
 int ATA_SS_IPM_PARTIAL ; 
 int ATA_SS_IPM_SLUMBER ; 
 int ATA_SS_SPD_GEN1 ; 
 int ATA_SS_SPD_GEN2 ; 
 int EINVAL ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* pci_read_config (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
ata_via_sata_scr_read(device_t dev, int port, int reg, u_int32_t *result)
{
	device_t parent;
	uint32_t val;

	parent = device_get_parent(dev);
	port = (port == 1) ? 1 : 0;
	switch (reg) {
	case ATA_SSTATUS:
		val = pci_read_config(parent, 0xa0 + port, 1);
		*result = val & 0x03;
		if (*result != ATA_SS_DET_NO_DEVICE) {
			if (val & 0x04)
				*result |= ATA_SS_IPM_PARTIAL;
			else if (val & 0x08)
				*result |= ATA_SS_IPM_SLUMBER;
			else
				*result |= ATA_SS_IPM_ACTIVE;
			if (val & 0x10)
				*result |= ATA_SS_SPD_GEN2;
			else
				*result |= ATA_SS_SPD_GEN1;
		}
		break;
	case ATA_SERROR:
		*result = pci_read_config(parent, 0xa8 + port * 4, 4);
		break;
	case ATA_SCONTROL:
		val = pci_read_config(parent, 0xa4 + port, 1);
		*result = 0;
		if (val & 0x01)
			*result |= ATA_SC_DET_RESET;
		if (val & 0x02)
			*result |= ATA_SC_DET_DISABLE;
		if (val & 0x04)
			*result |= ATA_SC_IPM_DIS_PARTIAL;
		if (val & 0x08)
			*result |= ATA_SC_IPM_DIS_SLUMBER;
		break;
	default:
		return (EINVAL);
	}
	return (0);
}