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
typedef  int u_int32_t ;
struct ata_pci_controller {int /*<<< orphan*/  r_res2; TYPE_1__* chip; } ;
struct ata_channel {int unit; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int cfg1; } ;

/* Variables and functions */
 int ATA_INB (int /*<<< orphan*/ ,int) ; 
 int ATA_INL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATA_OUTB (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int,int) ; 
 int NV4 ; 
 int NVQ ; 
 int /*<<< orphan*/  ata_sata_phy_check_events (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
ata_nvidia_status(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
    struct ata_channel *ch = device_get_softc(dev);
    int offset = ctlr->chip->cfg1 & NV4 ? 0x0440 : 0x0010;
    int shift = ch->unit << (ctlr->chip->cfg1 & NVQ ? 4 : 2);
    u_int32_t istatus;

    /* get interrupt status */
    if (ctlr->chip->cfg1 & NVQ)
	istatus = ATA_INL(ctlr->r_res2, offset);
    else
	istatus = ATA_INB(ctlr->r_res2, offset);

    /* do we have any PHY events ? */
    if (istatus & (0x0c << shift))
	ata_sata_phy_check_events(dev, -1);

    /* clear interrupt(s) */
    if (ctlr->chip->cfg1 & NVQ)
	ATA_OUTL(ctlr->r_res2, offset, (0x0f << shift) | 0x00f000f0);
    else
	ATA_OUTB(ctlr->r_res2, offset, (0x0f << shift));

    /* do we have any device action ? */
    return (istatus & (0x01 << shift));
}