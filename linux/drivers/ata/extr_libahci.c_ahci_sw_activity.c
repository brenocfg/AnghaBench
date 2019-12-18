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
struct ata_port {struct ahci_port_priv* private_data; } ;
struct ata_link {size_t pmp; int flags; struct ata_port* ap; } ;
struct ahci_port_priv {struct ahci_em_priv* em_priv; } ;
struct ahci_em_priv {int /*<<< orphan*/  timer; int /*<<< orphan*/  activity; } ;

/* Variables and functions */
 int ATA_LFLAG_SW_ACTIVITY ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ahci_sw_activity(struct ata_link *link)
{
	struct ata_port *ap = link->ap;
	struct ahci_port_priv *pp = ap->private_data;
	struct ahci_em_priv *emp = &pp->em_priv[link->pmp];

	if (!(link->flags & ATA_LFLAG_SW_ACTIVITY))
		return;

	emp->activity++;
	if (!timer_pending(&emp->timer))
		mod_timer(&emp->timer, jiffies + msecs_to_jiffies(10));
}