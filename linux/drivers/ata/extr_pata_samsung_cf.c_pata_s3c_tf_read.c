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
struct ata_taskfile {int flags; int ctl; void* hob_lbah; void* hob_lbam; void* hob_lbal; void* hob_nsect; void* hob_feature; void* device; void* lbah; void* lbam; void* lbal; void* nsect; void* feature; } ;
struct ata_ioports {int /*<<< orphan*/  ctl_addr; int /*<<< orphan*/  lbah_addr; int /*<<< orphan*/  lbam_addr; int /*<<< orphan*/  lbal_addr; int /*<<< orphan*/  nsect_addr; int /*<<< orphan*/  error_addr; int /*<<< orphan*/  device_addr; } ;
struct ata_port {int last_ctl; int /*<<< orphan*/  host; struct ata_ioports ioaddr; } ;

/* Variables and functions */
 int ATA_HOB ; 
 int ATA_TFLAG_LBA48 ; 
 void* ata_inb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_outb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pata_s3c_tf_read(struct ata_port *ap, struct ata_taskfile *tf)
{
	struct ata_ioports *ioaddr = &ap->ioaddr;

	tf->feature = ata_inb(ap->host, ioaddr->error_addr);
	tf->nsect = ata_inb(ap->host, ioaddr->nsect_addr);
	tf->lbal = ata_inb(ap->host, ioaddr->lbal_addr);
	tf->lbam = ata_inb(ap->host, ioaddr->lbam_addr);
	tf->lbah = ata_inb(ap->host, ioaddr->lbah_addr);
	tf->device = ata_inb(ap->host, ioaddr->device_addr);

	if (tf->flags & ATA_TFLAG_LBA48) {
		ata_outb(ap->host, tf->ctl | ATA_HOB, ioaddr->ctl_addr);
		tf->hob_feature = ata_inb(ap->host, ioaddr->error_addr);
		tf->hob_nsect = ata_inb(ap->host, ioaddr->nsect_addr);
		tf->hob_lbal = ata_inb(ap->host, ioaddr->lbal_addr);
		tf->hob_lbam = ata_inb(ap->host, ioaddr->lbam_addr);
		tf->hob_lbah = ata_inb(ap->host, ioaddr->lbah_addr);
		ata_outb(ap->host, tf->ctl, ioaddr->ctl_addr);
		ap->last_ctl = tf->ctl;
	}
}