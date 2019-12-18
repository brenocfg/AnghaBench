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
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct ata_port {int pflags; TYPE_2__ link; TYPE_1__* host; } ;
struct ahci_host_priv {int /*<<< orphan*/  (* stop_engine ) (struct ata_port*) ;int /*<<< orphan*/  (* start_engine ) (struct ata_port*) ;} ;
struct TYPE_3__ {struct ahci_host_priv* private_data; } ;

/* Variables and functions */
 int ATA_PFLAG_FROZEN ; 
 int /*<<< orphan*/  ata_dev_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sata_pmp_error_handler (struct ata_port*) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*) ; 
 int /*<<< orphan*/  stub2 (struct ata_port*) ; 
 int /*<<< orphan*/  stub3 (struct ata_port*) ; 

void ahci_error_handler(struct ata_port *ap)
{
	struct ahci_host_priv *hpriv = ap->host->private_data;

	if (!(ap->pflags & ATA_PFLAG_FROZEN)) {
		/* restart engine */
		hpriv->stop_engine(ap);
		hpriv->start_engine(ap);
	}

	sata_pmp_error_handler(ap);

	if (!ata_dev_enabled(ap->link.device))
		hpriv->stop_engine(ap);
}