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
struct ata_channel {scalar_t__ pm_level; int /*<<< orphan*/  conntask; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_SERROR ; 
 int ATA_SE_PHY_CHANGED ; 
 int /*<<< orphan*/  ATA_SSTATUS ; 
 int ATA_SS_DET_MASK ; 
 int ATA_SS_DET_PHY_ONLINE ; 
 int ATA_SS_IPM_ACTIVE ; 
 int ATA_SS_IPM_MASK ; 
 int ATA_SS_SPD_MASK ; 
 int ATA_SS_SPD_NO_SPEED ; 
 scalar_t__ ata_sata_scr_read (struct ata_channel*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ata_sata_scr_write (struct ata_channel*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bootverbose ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

void
ata_sata_phy_check_events(device_t dev, int port)
{
    struct ata_channel *ch = device_get_softc(dev);
    u_int32_t error, status;

    if (ata_sata_scr_read(ch, port, ATA_SERROR, &error))
	return;

    /* Check that SError value is sane. */
    if (error == 0xffffffff)
	return;

    /* Clear set error bits/interrupt. */
    if (error)
	ata_sata_scr_write(ch, port, ATA_SERROR, error);

    /* if we have a connection event deal with it */
    if ((error & ATA_SE_PHY_CHANGED) && (ch->pm_level == 0)) {
	if (bootverbose) {
	    if (ata_sata_scr_read(ch, port, ATA_SSTATUS, &status)) {
		    device_printf(dev, "PHYRDY change\n");
	    } else if (((status & ATA_SS_DET_MASK) == ATA_SS_DET_PHY_ONLINE) &&
		((status & ATA_SS_SPD_MASK) != ATA_SS_SPD_NO_SPEED) &&
		((status & ATA_SS_IPM_MASK) == ATA_SS_IPM_ACTIVE)) {
		    device_printf(dev, "CONNECT requested\n");
	    } else
		    device_printf(dev, "DISCONNECT requested\n");
	}
	taskqueue_enqueue(taskqueue_thread, &ch->conntask);
    }
}