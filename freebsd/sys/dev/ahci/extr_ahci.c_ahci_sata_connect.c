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
typedef  int u_int32_t ;
struct ahci_channel {int /*<<< orphan*/  r_mem; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_P_SERR ; 
 int /*<<< orphan*/  AHCI_P_SSTS ; 
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ATA_SS_DET_MASK ; 
 int ATA_SS_DET_NO_DEVICE ; 
 int ATA_SS_DET_PHY_OFFLINE ; 
 int ATA_SS_DET_PHY_ONLINE ; 
 int ATA_SS_IPM_ACTIVE ; 
 int ATA_SS_IPM_MASK ; 
 int ATA_SS_SPD_MASK ; 
 int ATA_SS_SPD_NO_SPEED ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int
ahci_sata_connect(struct ahci_channel *ch)
{
	u_int32_t status;
	int timeout, found = 0;

	/* Wait up to 100ms for "connect well" */
	for (timeout = 0; timeout < 1000 ; timeout++) {
		status = ATA_INL(ch->r_mem, AHCI_P_SSTS);
		if ((status & ATA_SS_DET_MASK) != ATA_SS_DET_NO_DEVICE)
			found = 1;
		if (((status & ATA_SS_DET_MASK) == ATA_SS_DET_PHY_ONLINE) &&
		    ((status & ATA_SS_SPD_MASK) != ATA_SS_SPD_NO_SPEED) &&
		    ((status & ATA_SS_IPM_MASK) == ATA_SS_IPM_ACTIVE))
			break;
		if ((status & ATA_SS_DET_MASK) == ATA_SS_DET_PHY_OFFLINE) {
			if (bootverbose) {
				device_printf(ch->dev, "SATA offline status=%08x\n",
				    status);
			}
			return (0);
		}
		if (found == 0 && timeout >= 100)
			break;
		DELAY(100);
	}
	if (timeout >= 1000 || !found) {
		if (bootverbose) {
			device_printf(ch->dev,
			    "SATA connect timeout time=%dus status=%08x\n",
			    timeout * 100, status);
		}
		return (0);
	}
	if (bootverbose) {
		device_printf(ch->dev, "SATA connect time=%dus status=%08x\n",
		    timeout * 100, status);
	}
	/* Clear SATA error register */
	ATA_OUTL(ch->r_mem, AHCI_P_SERR, 0xffffffff);
	return (1);
}