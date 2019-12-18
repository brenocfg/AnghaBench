#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nv_swncq_port_priv {scalar_t__ prd_dma; } ;
struct TYPE_3__ {unsigned int flags; } ;
struct ata_queued_cmd {int hw_tag; TYPE_1__ tf; } ;
struct TYPE_4__ {scalar_t__ bmdma_addr; } ;
struct ata_port {TYPE_2__ ioaddr; struct nv_swncq_port_priv* private_data; } ;

/* Variables and functions */
 scalar_t__ ATA_DMA_CMD ; 
 int ATA_DMA_START ; 
 scalar_t__ ATA_DMA_TABLE_OFS ; 
 int ATA_DMA_WR ; 
 int ATA_PRD_TBL_SZ ; 
 unsigned int ATA_TFLAG_WRITE ; 
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ata_bmdma_stop (struct ata_port*) ; 
 struct ata_queued_cmd* ata_qc_from_tag (struct ata_port*,int /*<<< orphan*/ ) ; 
 int ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (int,scalar_t__) ; 
 int /*<<< orphan*/  nv_swncq_tag (struct ata_port*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void nv_swncq_dmafis(struct ata_port *ap)
{
	struct ata_queued_cmd *qc;
	unsigned int rw;
	u8 dmactl;
	u32 tag;
	struct nv_swncq_port_priv *pp = ap->private_data;

	__ata_bmdma_stop(ap);
	tag = nv_swncq_tag(ap);

	DPRINTK("dma setup tag 0x%x\n", tag);
	qc = ata_qc_from_tag(ap, tag);

	if (unlikely(!qc))
		return;

	rw = qc->tf.flags & ATA_TFLAG_WRITE;

	/* load PRD table addr. */
	iowrite32(pp->prd_dma + ATA_PRD_TBL_SZ * qc->hw_tag,
		  ap->ioaddr.bmdma_addr + ATA_DMA_TABLE_OFS);

	/* specify data direction, triple-check start bit is clear */
	dmactl = ioread8(ap->ioaddr.bmdma_addr + ATA_DMA_CMD);
	dmactl &= ~ATA_DMA_WR;
	if (!rw)
		dmactl |= ATA_DMA_WR;

	iowrite8(dmactl | ATA_DMA_START, ap->ioaddr.bmdma_addr + ATA_DMA_CMD);
}