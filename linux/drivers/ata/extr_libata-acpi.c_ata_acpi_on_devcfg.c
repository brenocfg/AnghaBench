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
struct TYPE_6__ {int flags; } ;
struct ata_eh_context {TYPE_3__ i; } ;
struct TYPE_5__ {struct ata_eh_context eh_context; } ;
struct ata_port {int flags; int pflags; TYPE_2__ link; } ;
struct ata_device {int flags; TYPE_1__* link; } ;
struct TYPE_4__ {struct ata_port* ap; } ;

/* Variables and functions */
 int ATA_DFLAG_ACPI_DISABLED ; 
 int ATA_DFLAG_ACPI_FAILED ; 
 int ATA_DFLAG_ACPI_PENDING ; 
 int ATA_EHI_DID_HARDRESET ; 
 int ATA_FLAG_ACPI_SATA ; 
 int ATA_PFLAG_FROZEN ; 
 int EINVAL ; 
 int ENOENT ; 
 int ata_acpi_exec_tfs (struct ata_device*,int*) ; 
 int ata_acpi_push_id (struct ata_device*) ; 
 int /*<<< orphan*/  ata_dev_acpi_handle (struct ata_device*) ; 
 int /*<<< orphan*/  ata_dev_err (struct ata_device*,char*) ; 
 int ata_dev_reread_id (struct ata_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_dev_warn (struct ata_device*,char*) ; 

int ata_acpi_on_devcfg(struct ata_device *dev)
{
	struct ata_port *ap = dev->link->ap;
	struct ata_eh_context *ehc = &ap->link.eh_context;
	int acpi_sata = ap->flags & ATA_FLAG_ACPI_SATA;
	int nr_executed = 0;
	int rc;

	if (!ata_dev_acpi_handle(dev))
		return 0;

	/* do we need to do _GTF? */
	if (!(dev->flags & ATA_DFLAG_ACPI_PENDING) &&
	    !(acpi_sata && (ehc->i.flags & ATA_EHI_DID_HARDRESET)))
		return 0;

	/* do _SDD if SATA */
	if (acpi_sata) {
		rc = ata_acpi_push_id(dev);
		if (rc && rc != -ENOENT)
			goto acpi_err;
	}

	/* do _GTF */
	rc = ata_acpi_exec_tfs(dev, &nr_executed);
	if (rc)
		goto acpi_err;

	dev->flags &= ~ATA_DFLAG_ACPI_PENDING;

	/* refresh IDENTIFY page if any _GTF command has been executed */
	if (nr_executed) {
		rc = ata_dev_reread_id(dev, 0);
		if (rc < 0) {
			ata_dev_err(dev,
				    "failed to IDENTIFY after ACPI commands\n");
			return rc;
		}
	}

	return 0;

 acpi_err:
	/* ignore evaluation failure if we can continue safely */
	if (rc == -EINVAL && !nr_executed && !(ap->pflags & ATA_PFLAG_FROZEN))
		return 0;

	/* fail and let EH retry once more for unknown IO errors */
	if (!(dev->flags & ATA_DFLAG_ACPI_FAILED)) {
		dev->flags |= ATA_DFLAG_ACPI_FAILED;
		return rc;
	}

	dev->flags |= ATA_DFLAG_ACPI_DISABLED;
	ata_dev_warn(dev, "ACPI: failed the second time, disabled\n");

	/* We can safely continue if no _GTF command has been executed
	 * and port is not frozen.
	 */
	if (!nr_executed && !(ap->pflags & ATA_PFLAG_FROZEN))
		return 0;

	return rc;
}