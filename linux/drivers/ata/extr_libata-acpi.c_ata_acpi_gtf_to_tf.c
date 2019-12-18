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
struct ata_taskfile {int flags; int /*<<< orphan*/  command; int /*<<< orphan*/  device; int /*<<< orphan*/  lbah; int /*<<< orphan*/  lbam; int /*<<< orphan*/  lbal; int /*<<< orphan*/  nsect; int /*<<< orphan*/  feature; int /*<<< orphan*/  protocol; } ;
struct ata_device {int dummy; } ;
struct ata_acpi_gtf {int /*<<< orphan*/ * tf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_PROT_NODATA ; 
 int ATA_TFLAG_DEVICE ; 
 int ATA_TFLAG_ISADDR ; 
 int /*<<< orphan*/  ata_tf_init (struct ata_device*,struct ata_taskfile*) ; 

__attribute__((used)) static void ata_acpi_gtf_to_tf(struct ata_device *dev,
			       const struct ata_acpi_gtf *gtf,
			       struct ata_taskfile *tf)
{
	ata_tf_init(dev, tf);

	tf->flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	tf->protocol = ATA_PROT_NODATA;
	tf->feature = gtf->tf[0];	/* 0x1f1 */
	tf->nsect   = gtf->tf[1];	/* 0x1f2 */
	tf->lbal    = gtf->tf[2];	/* 0x1f3 */
	tf->lbam    = gtf->tf[3];	/* 0x1f4 */
	tf->lbah    = gtf->tf[4];	/* 0x1f5 */
	tf->device  = gtf->tf[5];	/* 0x1f6 */
	tf->command = gtf->tf[6];	/* 0x1f7 */
}