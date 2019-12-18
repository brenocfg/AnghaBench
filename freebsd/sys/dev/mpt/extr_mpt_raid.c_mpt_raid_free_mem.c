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
struct mpt_softc {int raid_max_volumes; scalar_t__ raid_max_disks; struct mpt_raid_volume* ioc_page3; struct mpt_raid_volume* ioc_page2; struct mpt_raid_volume* raid_disks; struct mpt_raid_volume* raid_volumes; } ;
struct mpt_raid_volume {struct mpt_raid_volume* config_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (struct mpt_raid_volume*,int /*<<< orphan*/ ) ; 

void
mpt_raid_free_mem(struct mpt_softc *mpt)
{

	if (mpt->raid_volumes) {
		struct mpt_raid_volume *mpt_raid;
		int i;
		for (i = 0; i < mpt->raid_max_volumes; i++) {
			mpt_raid = &mpt->raid_volumes[i];
			if (mpt_raid->config_page) {
				free(mpt_raid->config_page, M_DEVBUF);
				mpt_raid->config_page = NULL;
			}
		}
		free(mpt->raid_volumes, M_DEVBUF);
		mpt->raid_volumes = NULL;
	}
	if (mpt->raid_disks) {
		free(mpt->raid_disks, M_DEVBUF);
		mpt->raid_disks = NULL;
	}
	if (mpt->ioc_page2) {
		free(mpt->ioc_page2, M_DEVBUF);
		mpt->ioc_page2 = NULL;
	}
	if (mpt->ioc_page3) {
		free(mpt->ioc_page3, M_DEVBUF);
		mpt->ioc_page3 = NULL;
	}
	mpt->raid_max_volumes =  0;
	mpt->raid_max_disks =  0;
}