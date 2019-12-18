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
struct ata_link {unsigned long last_lpm_change; scalar_t__ lpm_policy; int flags; } ;

/* Variables and functions */
 int ATA_LFLAG_CHANGED ; 
 scalar_t__ ATA_LPM_MAX_POWER ; 
 int /*<<< orphan*/  ATA_TMOUT_SPURIOUS_PHY ; 
 int /*<<< orphan*/  jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,unsigned long) ; 

bool sata_lpm_ignore_phy_events(struct ata_link *link)
{
	unsigned long lpm_timeout = link->last_lpm_change +
				    msecs_to_jiffies(ATA_TMOUT_SPURIOUS_PHY);

	/* if LPM is enabled, PHYRDY doesn't mean anything */
	if (link->lpm_policy > ATA_LPM_MAX_POWER)
		return true;

	/* ignore the first PHY event after the LPM policy changed
	 * as it is might be spurious
	 */
	if ((link->flags & ATA_LFLAG_CHANGED) &&
	    time_before(jiffies, lpm_timeout))
		return true;

	return false;
}