#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct ata_channel {scalar_t__ pm_level; TYPE_1__* user; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_SCONTROL ; 
 int ATA_SC_DET_IDLE ; 
 int ATA_SC_DET_MASK ; 
 int ATA_SC_DET_RESET ; 
 int ATA_SC_IPM_DIS_PARTIAL ; 
 int ATA_SC_IPM_DIS_SLUMBER ; 
 int ATA_SC_SPD_SPEED_GEN1 ; 
 int ATA_SC_SPD_SPEED_GEN2 ; 
 int ATA_SC_SPD_SPEED_GEN3 ; 
 int /*<<< orphan*/  ATA_SERROR ; 
 int ata_sata_connect (struct ata_channel*,int,int) ; 
 scalar_t__ ata_sata_scr_read (struct ata_channel*,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ata_sata_scr_write (struct ata_channel*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ata_udelay (int) ; 
 scalar_t__ bootverbose ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

int
ata_sata_phy_reset(device_t dev, int port, int quick)
{
    struct ata_channel *ch = device_get_softc(dev);
    int loop, retry, sata_rev;
    uint32_t val, val1;

    sata_rev = ch->user[port < 0 ? 0 : port].revision;
    if (sata_rev > 0)
	quick = 0;

    if (quick) {
	if (ata_sata_scr_read(ch, port, ATA_SCONTROL, &val))
	    return (0);
	if ((val & ATA_SC_DET_MASK) == ATA_SC_DET_IDLE) {
	    ata_sata_scr_write(ch, port, ATA_SCONTROL,
		ATA_SC_DET_IDLE | ((ch->pm_level > 0) ? 0 :
		ATA_SC_IPM_DIS_PARTIAL | ATA_SC_IPM_DIS_SLUMBER));
	    return ata_sata_connect(ch, port, quick);
	}
    }

    if (bootverbose) {
	if (port < 0) {
	    device_printf(dev, "hard reset ...\n");
	} else {
	    device_printf(dev, "p%d: hard reset ...\n", port);
	}
    }
    if (sata_rev == 1)
	val1 = ATA_SC_SPD_SPEED_GEN1;
    else if (sata_rev == 2)
	val1 = ATA_SC_SPD_SPEED_GEN2;
    else if (sata_rev == 3)
	val1 = ATA_SC_SPD_SPEED_GEN3;
    else
	val1 = 0;
    for (retry = 0; retry < 10; retry++) {
	for (loop = 0; loop < 10; loop++) {
	    if (ata_sata_scr_write(ch, port, ATA_SCONTROL, ATA_SC_DET_RESET |
		    val1 | ATA_SC_IPM_DIS_PARTIAL | ATA_SC_IPM_DIS_SLUMBER))
		goto fail;
	    ata_udelay(100);
	    if (ata_sata_scr_read(ch, port, ATA_SCONTROL, &val))
		goto fail;
	    if ((val & ATA_SC_DET_MASK) == ATA_SC_DET_RESET)
		break;
	}
	ata_udelay(5000);
	for (loop = 0; loop < 10; loop++) {
	    if (ata_sata_scr_write(ch, port, ATA_SCONTROL,
		    ATA_SC_DET_IDLE | val1 | ((ch->pm_level > 0) ? 0 :
		    ATA_SC_IPM_DIS_PARTIAL | ATA_SC_IPM_DIS_SLUMBER)))
		goto fail;
	    ata_udelay(100);
	    if (ata_sata_scr_read(ch, port, ATA_SCONTROL, &val))
		goto fail;
	    if ((val & ATA_SC_DET_MASK) == 0)
		return ata_sata_connect(ch, port, 0);
	}
    }
fail:
    /* Clear SATA error register. */
    ata_sata_scr_write(ch, port, ATA_SERROR, 0xffffffff);

    if (bootverbose) {
	if (port < 0) {
	    device_printf(dev, "hard reset failed\n");
	} else {
	    device_printf(dev, "p%d: hard reset failed\n", port);
	}
    }
    return (0);
}