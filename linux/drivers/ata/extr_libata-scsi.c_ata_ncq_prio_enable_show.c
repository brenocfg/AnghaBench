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
struct scsi_device {int /*<<< orphan*/  host; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ata_port {int /*<<< orphan*/  lock; } ;
struct ata_device {int flags; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ATA_DFLAG_NCQ_PRIO_ENABLE ; 
 int ENODEV ; 
 struct ata_device* ata_scsi_find_dev (struct ata_port*,struct scsi_device*) ; 
 struct ata_port* ata_shost_to_port (int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t ata_ncq_prio_enable_show(struct device *device,
					struct device_attribute *attr,
					char *buf)
{
	struct scsi_device *sdev = to_scsi_device(device);
	struct ata_port *ap;
	struct ata_device *dev;
	bool ncq_prio_enable;
	int rc = 0;

	ap = ata_shost_to_port(sdev->host);

	spin_lock_irq(ap->lock);
	dev = ata_scsi_find_dev(ap, sdev);
	if (!dev) {
		rc = -ENODEV;
		goto unlock;
	}

	ncq_prio_enable = dev->flags & ATA_DFLAG_NCQ_PRIO_ENABLE;

unlock:
	spin_unlock_irq(ap->lock);

	return rc ? rc : snprintf(buf, 20, "%u\n", ncq_prio_enable);
}