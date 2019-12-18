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
struct mpt_softc {int /*<<< orphan*/  raid_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPT_RAID_SYNC_REPORT_INTERVAL ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_raid_timer ; 

__attribute__((used)) static void
mpt_schedule_raid_refresh(struct mpt_softc *mpt)
{

	callout_reset(&mpt->raid_timer, MPT_RAID_SYNC_REPORT_INTERVAL,
		      mpt_raid_timer, mpt);
}