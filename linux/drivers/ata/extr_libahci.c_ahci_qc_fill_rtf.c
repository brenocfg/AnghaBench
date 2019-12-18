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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_10__ {int /*<<< orphan*/  command; } ;
struct TYPE_8__ {scalar_t__ protocol; } ;
struct ata_queued_cmd {scalar_t__ dma_dir; int flags; TYPE_5__ result_tf; TYPE_3__ tf; TYPE_2__* dev; TYPE_4__* ap; } ;
struct ahci_port_priv {scalar_t__ fbs_enabled; int /*<<< orphan*/ * rx_fis; } ;
struct TYPE_9__ {struct ahci_port_priv* private_data; } ;
struct TYPE_7__ {TYPE_1__* link; } ;
struct TYPE_6__ {int pmp; } ;

/* Variables and functions */
 int AHCI_RX_FIS_SZ ; 
 scalar_t__ ATA_PROT_PIO ; 
 int ATA_QCFLAG_FAILED ; 
 scalar_t__ DMA_FROM_DEVICE ; 
 int RX_FIS_D2H_REG ; 
 int RX_FIS_PIO_SETUP ; 
 int /*<<< orphan*/  ata_tf_from_fis (int /*<<< orphan*/ *,TYPE_5__*) ; 

__attribute__((used)) static bool ahci_qc_fill_rtf(struct ata_queued_cmd *qc)
{
	struct ahci_port_priv *pp = qc->ap->private_data;
	u8 *rx_fis = pp->rx_fis;

	if (pp->fbs_enabled)
		rx_fis += qc->dev->link->pmp * AHCI_RX_FIS_SZ;

	/*
	 * After a successful execution of an ATA PIO data-in command,
	 * the device doesn't send D2H Reg FIS to update the TF and
	 * the host should take TF and E_Status from the preceding PIO
	 * Setup FIS.
	 */
	if (qc->tf.protocol == ATA_PROT_PIO && qc->dma_dir == DMA_FROM_DEVICE &&
	    !(qc->flags & ATA_QCFLAG_FAILED)) {
		ata_tf_from_fis(rx_fis + RX_FIS_PIO_SETUP, &qc->result_tf);
		qc->result_tf.command = (rx_fis + RX_FIS_PIO_SETUP)[15];
	} else
		ata_tf_from_fis(rx_fis + RX_FIS_D2H_REG, &qc->result_tf);

	return true;
}