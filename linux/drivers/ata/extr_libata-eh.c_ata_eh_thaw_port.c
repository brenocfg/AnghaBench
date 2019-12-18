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
struct ata_port {int /*<<< orphan*/  print_id; int /*<<< orphan*/  lock; TYPE_1__* ops; int /*<<< orphan*/  pflags; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* thaw ) (struct ata_port*) ;int /*<<< orphan*/  error_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_PFLAG_FROZEN ; 
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*) ; 

void ata_eh_thaw_port(struct ata_port *ap)
{
	unsigned long flags;

	if (!ap->ops->error_handler)
		return;

	spin_lock_irqsave(ap->lock, flags);

	ap->pflags &= ~ATA_PFLAG_FROZEN;

	if (ap->ops->thaw)
		ap->ops->thaw(ap);

	spin_unlock_irqrestore(ap->lock, flags);

	DPRINTK("ata%u port thawed\n", ap->print_id);
}