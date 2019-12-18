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
typedef  int u_int32_t ;
struct ata_pci_controller {int /*<<< orphan*/  r_res2; scalar_t__ chipset_data; TYPE_1__* chip; } ;
struct ata_channel {int unit; int /*<<< orphan*/  conntask; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int cfg2; } ;

/* Variables and functions */
 int ATA_INL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int,int) ; 
#define  PR_CMBO 132 
#define  PR_CMBO2 131 
#define  PR_PATA 130 
#define  PR_SATA 129 
#define  PR_SATA2 128 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

__attribute__((used)) static int
ata_promise_mio_status(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
    struct ata_channel *ch = device_get_softc(dev);
    u_int32_t stat_reg, vector, status;

    switch (ctlr->chip->cfg2) {
    case PR_PATA:
    case PR_CMBO:
    case PR_SATA:
	stat_reg = 0x6c;
	break;
    case PR_CMBO2: 
    case PR_SATA2:
    default:
	stat_reg = 0x60;
	break;
    }

    /* read and acknowledge interrupt */
    vector = (uint32_t)(uintptr_t)ctlr->chipset_data;

    /* read and clear interface status */
    status = ATA_INL(ctlr->r_res2, stat_reg);
    ATA_OUTL(ctlr->r_res2, stat_reg, status & (0x00000011 << ch->unit));

    /* check for and handle disconnect events */
    if (status & (0x00000001 << ch->unit)) {
	if (bootverbose)
	    device_printf(dev, "DISCONNECT requested\n");
	taskqueue_enqueue(taskqueue_thread, &ch->conntask);
    }

    /* check for and handle connect events */
    if (status & (0x00000010 << ch->unit)) {
	if (bootverbose)
	    device_printf(dev, "CONNECT requested\n");
	taskqueue_enqueue(taskqueue_thread, &ch->conntask);
    }

    /* do we have any device action ? */
    return (vector & (1 << (ch->unit + 1)));
}