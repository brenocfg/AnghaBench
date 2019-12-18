#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ata_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  pflags; struct ata_link* slave_link; } ;
struct TYPE_2__ {int flags; } ;
struct ata_eh_context {TYPE_1__ i; } ;
struct ata_eh_info {int dummy; } ;
struct ata_link {struct ata_eh_context eh_context; struct ata_eh_info eh_info; struct ata_port* ap; } ;
struct ata_device {int dummy; } ;

/* Variables and functions */
 int ATA_EHI_QUIET ; 
 int /*<<< orphan*/  ATA_PFLAG_RECOVERED ; 
 int /*<<< orphan*/  ata_eh_clear_action (struct ata_link*,struct ata_device*,struct ata_eh_info*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void ata_eh_about_to_do(struct ata_link *link, struct ata_device *dev,
			unsigned int action)
{
	struct ata_port *ap = link->ap;
	struct ata_eh_info *ehi = &link->eh_info;
	struct ata_eh_context *ehc = &link->eh_context;
	unsigned long flags;

	spin_lock_irqsave(ap->lock, flags);

	ata_eh_clear_action(link, dev, ehi, action);

	/* About to take EH action, set RECOVERED.  Ignore actions on
	 * slave links as master will do them again.
	 */
	if (!(ehc->i.flags & ATA_EHI_QUIET) && link != ap->slave_link)
		ap->pflags |= ATA_PFLAG_RECOVERED;

	spin_unlock_irqrestore(ap->lock, flags);
}