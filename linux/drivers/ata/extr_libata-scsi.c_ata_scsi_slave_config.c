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
struct ata_port {int dummy; } ;
struct ata_device {int dummy; } ;

/* Variables and functions */
 struct ata_device* __ata_scsi_find_dev (struct ata_port*,struct scsi_device*) ; 
 int ata_scsi_dev_config (struct scsi_device*,struct ata_device*) ; 
 int /*<<< orphan*/  ata_scsi_sdev_config (struct scsi_device*) ; 
 struct ata_port* ata_shost_to_port (int /*<<< orphan*/ ) ; 

int ata_scsi_slave_config(struct scsi_device *sdev)
{
	struct ata_port *ap = ata_shost_to_port(sdev->host);
	struct ata_device *dev = __ata_scsi_find_dev(ap, sdev);
	int rc = 0;

	ata_scsi_sdev_config(sdev);

	if (dev)
		rc = ata_scsi_dev_config(sdev, dev);

	return rc;
}