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
struct scsi_device {int /*<<< orphan*/  host; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ata_port {int /*<<< orphan*/  lock; } ;
struct ata_device {int flags; TYPE_2__* link; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  action; } ;
struct TYPE_4__ {TYPE_1__ eh_info; } ;

/* Variables and functions */
 int ATA_DFLAG_NCQ_PRIO ; 
 int ATA_DFLAG_NCQ_PRIO_ENABLE ; 
 int /*<<< orphan*/  ATA_EHI_QUIET ; 
 int /*<<< orphan*/  ATA_EH_REVALIDATE ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  ata_port_schedule_eh (struct ata_port*) ; 
 int /*<<< orphan*/  ata_port_wait_eh (struct ata_port*) ; 
 struct ata_device* ata_scsi_find_dev (struct ata_port*,struct scsi_device*) ; 
 struct ata_port* ata_shost_to_port (int /*<<< orphan*/ ) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t ata_ncq_prio_enable_store(struct device *device,
					 struct device_attribute *attr,
					 const char *buf, size_t len)
{
	struct scsi_device *sdev = to_scsi_device(device);
	struct ata_port *ap;
	struct ata_device *dev;
	long int input;
	int rc;

	rc = kstrtol(buf, 10, &input);
	if (rc)
		return rc;
	if ((input < 0) || (input > 1))
		return -EINVAL;

	ap = ata_shost_to_port(sdev->host);
	dev = ata_scsi_find_dev(ap, sdev);
	if (unlikely(!dev))
		return  -ENODEV;

	spin_lock_irq(ap->lock);
	if (input)
		dev->flags |= ATA_DFLAG_NCQ_PRIO_ENABLE;
	else
		dev->flags &= ~ATA_DFLAG_NCQ_PRIO_ENABLE;

	dev->link->eh_info.action |= ATA_EH_REVALIDATE;
	dev->link->eh_info.flags |= ATA_EHI_QUIET;
	ata_port_schedule_eh(ap);
	spin_unlock_irq(ap->lock);

	ata_port_wait_eh(ap);

	if (input) {
		spin_lock_irq(ap->lock);
		if (!(dev->flags & ATA_DFLAG_NCQ_PRIO)) {
			dev->flags &= ~ATA_DFLAG_NCQ_PRIO_ENABLE;
			rc = -EIO;
		}
		spin_unlock_irq(ap->lock);
	}

	return rc ? rc : len;
}