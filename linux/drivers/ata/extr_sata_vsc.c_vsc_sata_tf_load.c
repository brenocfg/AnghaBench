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
typedef  int u16 ;
struct ata_taskfile {unsigned int flags; int ctl; int feature; int nsect; int lbal; int lbam; int lbah; int /*<<< orphan*/  device; scalar_t__ hob_lbah; scalar_t__ hob_lbam; scalar_t__ hob_lbal; scalar_t__ hob_nsect; scalar_t__ hob_feature; } ;
struct ata_ioports {int /*<<< orphan*/  device_addr; int /*<<< orphan*/  lbah_addr; int /*<<< orphan*/  lbam_addr; int /*<<< orphan*/  lbal_addr; int /*<<< orphan*/  nsect_addr; int /*<<< orphan*/  feature_addr; } ;
struct ata_port {int last_ctl; struct ata_ioports ioaddr; } ;

/* Variables and functions */
 int ATA_NIEN ; 
 int ATA_TFLAG_DEVICE ; 
 unsigned int ATA_TFLAG_ISADDR ; 
 int ATA_TFLAG_LBA48 ; 
 int /*<<< orphan*/  ata_wait_idle (struct ata_port*) ; 
 int /*<<< orphan*/  vsc_intr_mask_update (struct ata_port*,int) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vsc_sata_tf_load(struct ata_port *ap, const struct ata_taskfile *tf)
{
	struct ata_ioports *ioaddr = &ap->ioaddr;
	unsigned int is_addr = tf->flags & ATA_TFLAG_ISADDR;

	/*
	 * The only thing the ctl register is used for is SRST.
	 * That is not enabled or disabled via tf_load.
	 * However, if ATA_NIEN is changed, then we need to change
	 * the interrupt register.
	 */
	if ((tf->ctl & ATA_NIEN) != (ap->last_ctl & ATA_NIEN)) {
		ap->last_ctl = tf->ctl;
		vsc_intr_mask_update(ap, tf->ctl & ATA_NIEN);
	}
	if (is_addr && (tf->flags & ATA_TFLAG_LBA48)) {
		writew(tf->feature | (((u16)tf->hob_feature) << 8),
		       ioaddr->feature_addr);
		writew(tf->nsect | (((u16)tf->hob_nsect) << 8),
		       ioaddr->nsect_addr);
		writew(tf->lbal | (((u16)tf->hob_lbal) << 8),
		       ioaddr->lbal_addr);
		writew(tf->lbam | (((u16)tf->hob_lbam) << 8),
		       ioaddr->lbam_addr);
		writew(tf->lbah | (((u16)tf->hob_lbah) << 8),
		       ioaddr->lbah_addr);
	} else if (is_addr) {
		writew(tf->feature, ioaddr->feature_addr);
		writew(tf->nsect, ioaddr->nsect_addr);
		writew(tf->lbal, ioaddr->lbal_addr);
		writew(tf->lbam, ioaddr->lbam_addr);
		writew(tf->lbah, ioaddr->lbah_addr);
	}

	if (tf->flags & ATA_TFLAG_DEVICE)
		writeb(tf->device, ioaddr->device_addr);

	ata_wait_idle(ap);
}