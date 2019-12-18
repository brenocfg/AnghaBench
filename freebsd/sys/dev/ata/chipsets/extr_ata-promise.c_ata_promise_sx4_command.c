#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int32_t ;
struct TYPE_4__ {int command; } ;
struct TYPE_5__ {TYPE_1__ ata; } ;
struct ata_request {int bytecount; int flags; TYPE_3__* dma; TYPE_2__ u; int /*<<< orphan*/  parent; } ;
struct ata_pci_controller {int /*<<< orphan*/  r_res2; int /*<<< orphan*/  r_res1; } ;
struct ata_dma_prdentry {int count; int addr; } ;
struct ata_channel {int unit; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int caddr_t ;
struct TYPE_6__ {struct ata_dma_prdentry* sg; } ;

/* Variables and functions */
#define  ATA_ATA_IDENTIFY 145 
 int ATA_DMA_EOT ; 
#define  ATA_FLUSHCACHE 144 
#define  ATA_FLUSHCACHE48 143 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int,int) ; 
 int ATA_PDC_APKT_OFFSET ; 
 int ATA_PDC_ASG_OFFSET ; 
 int ATA_PDC_BUF_BASE ; 
 int ATA_PDC_BUF_OFFSET ; 
 int ATA_PDC_CHN_OFFSET ; 
 int ATA_PDC_HPKT_OFFSET ; 
 int ATA_PDC_HSG_OFFSET ; 
 int ATA_PDC_LSG_OFFSET ; 
#define  ATA_READ 142 
#define  ATA_READ48 141 
#define  ATA_READ_DMA 140 
#define  ATA_READ_DMA48 139 
#define  ATA_READ_MUL 138 
#define  ATA_READ_MUL48 137 
 int ATA_R_READ ; 
 int ATA_R_WRITE ; 
#define  ATA_SETFEATURES 136 
#define  ATA_SET_MULTI 135 
#define  ATA_SLEEP 134 
#define  ATA_WRITE 133 
#define  ATA_WRITE48 132 
#define  ATA_WRITE_DMA 131 
#define  ATA_WRITE_DMA48 130 
#define  ATA_WRITE_MUL 129 
#define  ATA_WRITE_MUL48 128 
 int ata_generic_command (struct ata_request*) ; 
 int /*<<< orphan*/  ata_promise_apkt (int /*<<< orphan*/ *,struct ata_request*) ; 
 int /*<<< orphan*/  ata_promise_queue_hpkt (struct ata_pci_controller*,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int htole32 (int) ; 
 int rman_get_virtual (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_promise_sx4_command(struct ata_request *request)
{
    device_t gparent = device_get_parent(request->parent);
    struct ata_pci_controller *ctlr = device_get_softc(gparent);
    struct ata_channel *ch = device_get_softc(request->parent);
    struct ata_dma_prdentry *prd;
    caddr_t window = rman_get_virtual(ctlr->r_res1);
    u_int32_t *wordp;
    int i, idx, length = 0;

    /* XXX SOS add ATAPI commands support later */
    switch (request->u.ata.command) {    

    default:
	return -1;

    case ATA_ATA_IDENTIFY:
    case ATA_READ:
    case ATA_READ48:
    case ATA_READ_MUL:
    case ATA_READ_MUL48:
    case ATA_WRITE:
    case ATA_WRITE48:
    case ATA_WRITE_MUL:
    case ATA_WRITE_MUL48:
	ATA_OUTL(ctlr->r_res2, 0x000c0400 + ((ch->unit + 1) << 2), 0x00000001);
	return ata_generic_command(request);

    case ATA_SETFEATURES:
    case ATA_FLUSHCACHE:
    case ATA_FLUSHCACHE48:
    case ATA_SLEEP:
    case ATA_SET_MULTI:
	wordp = (u_int32_t *)
	    (window + (ch->unit * ATA_PDC_CHN_OFFSET) + ATA_PDC_APKT_OFFSET);
	wordp[0] = htole32(0x08 | ((ch->unit + 1)<<16) | (0x00 << 24));
	wordp[1] = 0;
	wordp[2] = 0;
	ata_promise_apkt((u_int8_t *)wordp, request);
	ATA_OUTL(ctlr->r_res2, 0x000c0484, 0x00000001);
	ATA_OUTL(ctlr->r_res2, 0x000c0400 + ((ch->unit + 1) << 2), 0x00000001);
	ATA_OUTL(ctlr->r_res2, 0x000c0240 + (ch->unit << 7),
		 htole32((ch->unit * ATA_PDC_CHN_OFFSET)+ATA_PDC_APKT_OFFSET));
	return 0;

    case ATA_READ_DMA:
    case ATA_READ_DMA48:
    case ATA_WRITE_DMA:
    case ATA_WRITE_DMA48:
	prd = request->dma->sg;
	wordp = (u_int32_t *)
	    (window + (ch->unit * ATA_PDC_CHN_OFFSET) + ATA_PDC_HSG_OFFSET);
	i = idx = 0;
	do {
	    wordp[idx++] = prd[i].addr;
	    wordp[idx++] = prd[i].count;
	    length += (prd[i].count & ~ATA_DMA_EOT);
	} while (!(prd[i++].count & ATA_DMA_EOT));

	wordp = (u_int32_t *)
	    (window + (ch->unit * ATA_PDC_CHN_OFFSET) + ATA_PDC_LSG_OFFSET);
	wordp[0] = htole32((ch->unit * ATA_PDC_BUF_OFFSET) + ATA_PDC_BUF_BASE);
	wordp[1] = htole32(request->bytecount | ATA_DMA_EOT);

	wordp = (u_int32_t *)
	    (window + (ch->unit * ATA_PDC_CHN_OFFSET) + ATA_PDC_ASG_OFFSET);
	wordp[0] = htole32((ch->unit * ATA_PDC_BUF_OFFSET) + ATA_PDC_BUF_BASE);
	wordp[1] = htole32(request->bytecount | ATA_DMA_EOT);

	wordp = (u_int32_t *)
	    (window + (ch->unit * ATA_PDC_CHN_OFFSET) + ATA_PDC_HPKT_OFFSET);
	if (request->flags & ATA_R_READ)
	    wordp[0] = htole32(0x14 | ((ch->unit+9)<<16) | ((ch->unit+5)<<24));
	if (request->flags & ATA_R_WRITE)
	    wordp[0] = htole32(0x00 | ((ch->unit+13)<<16) | (0x00<<24));
	wordp[1] = htole32((ch->unit * ATA_PDC_CHN_OFFSET)+ATA_PDC_HSG_OFFSET);
	wordp[2] = htole32((ch->unit * ATA_PDC_CHN_OFFSET)+ATA_PDC_LSG_OFFSET);
	wordp[3] = 0;

	wordp = (u_int32_t *)
	    (window + (ch->unit * ATA_PDC_CHN_OFFSET) + ATA_PDC_APKT_OFFSET);
	if (request->flags & ATA_R_READ)
	    wordp[0] = htole32(0x04 | ((ch->unit+5)<<16) | (0x00<<24));
	if (request->flags & ATA_R_WRITE)
	    wordp[0] = htole32(0x10 | ((ch->unit+1)<<16) | ((ch->unit+13)<<24));
	wordp[1] = htole32((ch->unit * ATA_PDC_CHN_OFFSET)+ATA_PDC_ASG_OFFSET);
	wordp[2] = 0;
	ata_promise_apkt((u_int8_t *)wordp, request);
	ATA_OUTL(ctlr->r_res2, 0x000c0484, 0x00000001);

	if (request->flags & ATA_R_READ) {
	    ATA_OUTL(ctlr->r_res2, 0x000c0400 + ((ch->unit+5)<<2), 0x00000001);
	    ATA_OUTL(ctlr->r_res2, 0x000c0400 + ((ch->unit+9)<<2), 0x00000001);
	    ATA_OUTL(ctlr->r_res2, 0x000c0240 + (ch->unit << 7),
		htole32((ch->unit * ATA_PDC_CHN_OFFSET) + ATA_PDC_APKT_OFFSET));
	}
	if (request->flags & ATA_R_WRITE) {
	    ATA_OUTL(ctlr->r_res2, 0x000c0400 + ((ch->unit+1)<<2), 0x00000001);
	    ATA_OUTL(ctlr->r_res2, 0x000c0400 + ((ch->unit+13)<<2), 0x00000001);
	    ata_promise_queue_hpkt(ctlr,
		htole32((ch->unit * ATA_PDC_CHN_OFFSET) + ATA_PDC_HPKT_OFFSET));
	}
	return 0;
    }
}