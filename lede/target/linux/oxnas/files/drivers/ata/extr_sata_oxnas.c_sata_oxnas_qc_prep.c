#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sata_oxnas_port_priv {scalar_t__ sgdma_base; TYPE_2__* sgdma_request; int /*<<< orphan*/  sgdma_request_pa; } ;
struct TYPE_5__ {int /*<<< orphan*/  protocol; } ;
struct ata_queued_cmd {scalar_t__ dma_dir; TYPE_3__* ap; TYPE_1__ tf; int /*<<< orphan*/  err_mask; } ;
struct TYPE_7__ {int port_no; int /*<<< orphan*/  bmdma_prd_dma; struct sata_oxnas_port_priv* private_data; int /*<<< orphan*/  host; } ;
struct TYPE_6__ {int /*<<< orphan*/  dst_pa; int /*<<< orphan*/  src_pa; int /*<<< orphan*/  qualifier; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_ERR_ATA_BUS ; 
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ SGDMA_CONTROL ; 
 int /*<<< orphan*/  SGDMA_CONTROL_NOGO ; 
 int /*<<< orphan*/  SGDMA_REQCTL0IN ; 
 int /*<<< orphan*/  SGDMA_REQCTL0OUT ; 
 int /*<<< orphan*/  SGDMA_REQCTL1IN ; 
 int /*<<< orphan*/  SGDMA_REQCTL1OUT ; 
 int /*<<< orphan*/  SGDMA_REQQUAL ; 
 scalar_t__ SGDMA_REQUESTPTR ; 
 int /*<<< orphan*/  ata_bmdma_qc_prep (struct ata_queued_cmd*) ; 
 scalar_t__ ata_is_dma (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_is_pio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_port_err (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  ata_qc_complete (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sata_oxnas_check_link (TYPE_3__*) ; 
 int /*<<< orphan*/  sata_oxnas_reset_ucode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void sata_oxnas_qc_prep(struct ata_queued_cmd *qc)
{
	struct sata_oxnas_port_priv *pd;
	int port_no = qc->ap->port_no;

	/* if the port's not connected, complete now with an error */
	if (!sata_oxnas_check_link(qc->ap)) {
		ata_port_err(qc->ap,
			"port %d not connected completing with error\n",
			port_no);
		qc->err_mask |= AC_ERR_ATA_BUS;
		ata_qc_complete(qc);
	}

	sata_oxnas_reset_ucode(qc->ap->host, 0, 0);

	/* both pio and dma commands use dma */
	if (ata_is_dma(qc->tf.protocol) || ata_is_pio(qc->tf.protocol)) {

		/* program the scatterlist into the prd table */
		ata_bmdma_qc_prep(qc);

		/* point the sgdma controller at the dma request structure */
		pd = qc->ap->private_data;

		iowrite32(pd->sgdma_request_pa,
				pd->sgdma_base + SGDMA_REQUESTPTR);

		/* setup the request table */
		if (port_no == 0) {
			pd->sgdma_request->control =
				(qc->dma_dir == DMA_FROM_DEVICE) ?
					SGDMA_REQCTL0IN : SGDMA_REQCTL0OUT;
		} else {
			pd->sgdma_request->control =
				(qc->dma_dir == DMA_FROM_DEVICE) ?
					SGDMA_REQCTL1IN : SGDMA_REQCTL1OUT;
		}
		pd->sgdma_request->qualifier = SGDMA_REQQUAL;
		pd->sgdma_request->src_pa = qc->ap->bmdma_prd_dma;
		pd->sgdma_request->dst_pa = qc->ap->bmdma_prd_dma;
		smp_wmb();

		/* tell it to wait */
		iowrite32(SGDMA_CONTROL_NOGO, pd->sgdma_base + SGDMA_CONTROL);
	}
}