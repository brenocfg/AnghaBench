#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct xgene_ahci_context {scalar_t__* class; scalar_t__* last_cmd; } ;
struct TYPE_8__ {scalar_t__ command; } ;
struct ata_queued_cmd {TYPE_4__ tf; TYPE_3__* dev; struct ata_port* ap; } ;
struct ata_port {size_t port_no; TYPE_1__* host; } ;
struct ahci_host_priv {struct xgene_ahci_context* plat_data; } ;
struct TYPE_7__ {TYPE_2__* link; } ;
struct TYPE_6__ {int pmp; } ;
struct TYPE_5__ {struct ahci_host_priv* private_data; } ;

/* Variables and functions */
 scalar_t__ ATA_CMD_ID_ATA ; 
 scalar_t__ ATA_CMD_PACKET ; 
 scalar_t__ ATA_CMD_SMART ; 
 scalar_t__ ATA_DEV_PMP ; 
 int PORT_FBS ; 
 int PORT_FBS_DEV_MASK ; 
 int PORT_FBS_DEV_OFFSET ; 
 void* ahci_port_base (struct ata_port*) ; 
 int ahci_qc_issue (struct ata_queued_cmd*) ; 
 int readl (void*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (int,void*) ; 
 int /*<<< orphan*/  xgene_ahci_restart_engine (struct ata_port*) ; 

__attribute__((used)) static unsigned int xgene_ahci_qc_issue(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct ahci_host_priv *hpriv = ap->host->private_data;
	struct xgene_ahci_context *ctx = hpriv->plat_data;
	int rc = 0;
	u32 port_fbs;
	void *port_mmio = ahci_port_base(ap);

	/*
	 * Write the pmp value to PxFBS.DEV
	 * for case of Port Mulitplier.
	 */
	if (ctx->class[ap->port_no] == ATA_DEV_PMP) {
		port_fbs = readl(port_mmio + PORT_FBS);
		port_fbs &= ~PORT_FBS_DEV_MASK;
		port_fbs |= qc->dev->link->pmp << PORT_FBS_DEV_OFFSET;
		writel(port_fbs, port_mmio + PORT_FBS);
	}

	if (unlikely((ctx->last_cmd[ap->port_no] == ATA_CMD_ID_ATA) ||
	    (ctx->last_cmd[ap->port_no] == ATA_CMD_PACKET) ||
	    (ctx->last_cmd[ap->port_no] == ATA_CMD_SMART)))
		xgene_ahci_restart_engine(ap);

	rc = ahci_qc_issue(qc);

	/* Save the last command issued */
	ctx->last_cmd[ap->port_no] = qc->tf.command;

	return rc;
}