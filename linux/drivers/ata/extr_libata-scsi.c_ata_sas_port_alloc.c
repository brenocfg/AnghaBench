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
struct ata_port_info {int /*<<< orphan*/  port_ops; int /*<<< orphan*/  flags; int /*<<< orphan*/  udma_mask; int /*<<< orphan*/  mwdma_mask; int /*<<< orphan*/  pio_mask; } ;
struct ata_port {int /*<<< orphan*/  cbl; int /*<<< orphan*/  ops; int /*<<< orphan*/  flags; int /*<<< orphan*/  udma_mask; int /*<<< orphan*/  mwdma_mask; int /*<<< orphan*/  pio_mask; int /*<<< orphan*/ * lock; scalar_t__ port_no; } ;
struct ata_host {int /*<<< orphan*/  lock; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CBL_SATA ; 
 struct ata_port* ata_port_alloc (struct ata_host*) ; 

struct ata_port *ata_sas_port_alloc(struct ata_host *host,
				    struct ata_port_info *port_info,
				    struct Scsi_Host *shost)
{
	struct ata_port *ap;

	ap = ata_port_alloc(host);
	if (!ap)
		return NULL;

	ap->port_no = 0;
	ap->lock = &host->lock;
	ap->pio_mask = port_info->pio_mask;
	ap->mwdma_mask = port_info->mwdma_mask;
	ap->udma_mask = port_info->udma_mask;
	ap->flags |= port_info->flags;
	ap->ops = port_info->port_ops;
	ap->cbl = ATA_CBL_SATA;

	return ap;
}