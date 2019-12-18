#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int target_id; } ;
union ccb {TYPE_2__ ccb_h; } ;
typedef  int /*<<< orphan*/  target_id_t ;
struct mpt_softc {scalar_t__ raid_max_disks; struct mpt_raid_disk* raid_disks; } ;
struct TYPE_3__ {int /*<<< orphan*/  PhysDiskID; } ;
struct mpt_raid_disk {int flags; TYPE_1__ config_page; } ;
typedef  int cam_status ;

/* Variables and functions */
 int /*<<< orphan*/  MPT_PRT_DEBUG1 ; 
 int MPT_RDF_ACTIVE ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*,int) ; 

cam_status
mpt_map_physdisk(struct mpt_softc *mpt, union ccb *ccb, target_id_t *tgt)
{
	struct mpt_raid_disk *mpt_disk;

	mpt_disk = mpt->raid_disks + ccb->ccb_h.target_id;
	if (ccb->ccb_h.target_id < mpt->raid_max_disks
	 && (mpt_disk->flags & MPT_RDF_ACTIVE) != 0) {
		*tgt = mpt_disk->config_page.PhysDiskID;
		return (0);
	}
	mpt_lprt(mpt, MPT_PRT_DEBUG1, "mpt_map_physdisk(%d) - Not Active\n",
		 ccb->ccb_h.target_id);
	return (-1);
}