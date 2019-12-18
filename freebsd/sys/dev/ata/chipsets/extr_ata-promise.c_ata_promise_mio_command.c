#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  scalar_t__ u_int32_t ;
struct TYPE_7__ {int command; } ;
struct TYPE_8__ {TYPE_2__ ata; } ;
struct ata_request {int unit; TYPE_4__* dma; TYPE_3__ u; int /*<<< orphan*/  parent; } ;
struct ata_pci_controller {int /*<<< orphan*/  r_res2; TYPE_1__* chip; } ;
struct TYPE_10__ {int work_bus; scalar_t__ work; } ;
struct ata_channel {int unit; TYPE_5__ dma; } ;
struct TYPE_9__ {int sg_bus; } ;
struct TYPE_6__ {scalar_t__ cfg2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_OUTB (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int,int) ; 
#define  ATA_READ_DMA 131 
#define  ATA_READ_DMA48 130 
#define  ATA_WRITE_DMA 129 
#define  ATA_WRITE_DMA48 128 
 scalar_t__ PR_CMBO2 ; 
 scalar_t__ PR_SATA2 ; 
 int ata_generic_command (struct ata_request*) ; 
 int /*<<< orphan*/  ata_promise_apkt (int /*<<< orphan*/ *,struct ata_request*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ htole32 (int) ; 

__attribute__((used)) static int
ata_promise_mio_command(struct ata_request *request)
{
    struct ata_pci_controller *ctlr=device_get_softc(device_get_parent(request->parent));
    struct ata_channel *ch = device_get_softc(request->parent);

    u_int32_t *wordp = (u_int32_t *)ch->dma.work;

    ATA_OUTL(ctlr->r_res2, (ch->unit + 1) << 2, 0x00000001);

    if ((ctlr->chip->cfg2 == PR_SATA2) ||
        ((ctlr->chip->cfg2 == PR_CMBO2) && (ch->unit < 2))) {
	/* set portmultiplier port */
	ATA_OUTB(ctlr->r_res2, 0x4e8 + (ch->unit << 8), request->unit & 0x0f);
    }

    /* XXX SOS add ATAPI commands support later */
    switch (request->u.ata.command) {
    default:
	return ata_generic_command(request);

    case ATA_READ_DMA:
    case ATA_READ_DMA48:
	wordp[0] = htole32(0x04 | ((ch->unit + 1) << 16) | (0x00 << 24));
	break;

    case ATA_WRITE_DMA:
    case ATA_WRITE_DMA48:
	wordp[0] = htole32(0x00 | ((ch->unit + 1) << 16) | (0x00 << 24));
	break;
    }
    wordp[1] = htole32(request->dma->sg_bus);
    wordp[2] = 0;
    ata_promise_apkt((u_int8_t*)wordp, request);

    ATA_OUTL(ctlr->r_res2, 0x0240 + (ch->unit << 7), ch->dma.work_bus);
    return 0;
}