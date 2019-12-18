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
struct scsi_host_template {int dummy; } ;
struct ata_host {int /*<<< orphan*/  dev; struct ahci_host_priv* private_data; } ;
struct ahci_host_priv {int irq; int flags; scalar_t__ irq_handler; int /*<<< orphan*/  get_irq_vector; } ;

/* Variables and functions */
 int AHCI_HFLAG_MULTI_MSI ; 
 int EIO ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int ahci_host_activate_multi_irqs (struct ata_host*,struct scsi_host_template*) ; 
 scalar_t__ ahci_single_level_irq_intr ; 
 int ata_host_activate (struct ata_host*,int,scalar_t__,int /*<<< orphan*/ ,struct scsi_host_template*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 

int ahci_host_activate(struct ata_host *host, struct scsi_host_template *sht)
{
	struct ahci_host_priv *hpriv = host->private_data;
	int irq = hpriv->irq;
	int rc;

	if (hpriv->flags & AHCI_HFLAG_MULTI_MSI) {
		if (hpriv->irq_handler &&
		    hpriv->irq_handler != ahci_single_level_irq_intr)
			dev_warn(host->dev,
			         "both AHCI_HFLAG_MULTI_MSI flag set and custom irq handler implemented\n");
		if (!hpriv->get_irq_vector) {
			dev_err(host->dev,
				"AHCI_HFLAG_MULTI_MSI requires ->get_irq_vector!\n");
			return -EIO;
		}

		rc = ahci_host_activate_multi_irqs(host, sht);
	} else {
		rc = ata_host_activate(host, irq, hpriv->irq_handler,
				       IRQF_SHARED, sht);
	}


	return rc;
}