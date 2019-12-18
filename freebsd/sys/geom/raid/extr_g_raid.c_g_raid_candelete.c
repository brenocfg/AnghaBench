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
typedef  int /*<<< orphan*/  val ;
struct g_raid_volume {int v_disks_count; struct g_raid_subdisk* v_subdisks; } ;
struct g_raid_subdisk {scalar_t__ sd_state; TYPE_1__* sd_disk; } ;
struct g_raid_softc {int dummy; } ;
struct g_provider {struct g_raid_volume* private; } ;
struct bio {struct g_provider* bio_to; } ;
struct TYPE_2__ {scalar_t__ d_candelete; } ;

/* Variables and functions */
 scalar_t__ G_RAID_SUBDISK_S_NONE ; 
 int /*<<< orphan*/  g_handleattr (struct bio*,char*,int*,int) ; 

__attribute__((used)) static void
g_raid_candelete(struct g_raid_softc *sc, struct bio *bp)
{
	struct g_provider *pp;
	struct g_raid_volume *vol;
	struct g_raid_subdisk *sd;
	int i, val;

	pp = bp->bio_to;
	vol = pp->private;
	for (i = 0; i < vol->v_disks_count; i++) {
		sd = &vol->v_subdisks[i];
		if (sd->sd_state == G_RAID_SUBDISK_S_NONE)
			continue;
		if (sd->sd_disk->d_candelete)
			break;
	}
	val = i < vol->v_disks_count;
	g_handleattr(bp, "GEOM::candelete", &val, sizeof(val));
}