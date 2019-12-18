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
struct scsi_device {int dummy; } ;
struct ata_port {int dummy; } ;
struct ata_device {int dummy; } ;

/* Variables and functions */
 struct ata_device* __ata_scsi_find_dev (struct ata_port*,struct scsi_device const*) ; 
 int /*<<< orphan*/  ata_dev_enabled (struct ata_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct ata_device *
ata_scsi_find_dev(struct ata_port *ap, const struct scsi_device *scsidev)
{
	struct ata_device *dev = __ata_scsi_find_dev(ap, scsidev);

	if (unlikely(!dev || !ata_dev_enabled(dev)))
		return NULL;

	return dev;
}