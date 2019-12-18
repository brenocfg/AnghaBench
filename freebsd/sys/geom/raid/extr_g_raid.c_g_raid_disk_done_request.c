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
struct g_raid_volume {int /*<<< orphan*/  v_tr; } ;
struct g_raid_subdisk {scalar_t__ sd_offset; struct g_raid_volume* sd_volume; struct g_raid_softc* sd_softc; } ;
struct g_raid_softc {int dummy; } ;
struct g_raid_disk {int dummy; } ;
struct bio {int /*<<< orphan*/  bio_offset; TYPE_1__* bio_from; struct g_raid_subdisk* bio_caller1; int /*<<< orphan*/  bio_error; } ;
struct TYPE_2__ {struct g_raid_disk* private; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_LOGREQ (int,struct bio*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_RAID_TR_IODONE (int /*<<< orphan*/ ,struct g_raid_subdisk*,struct bio*) ; 
 int /*<<< orphan*/  g_raid_kill_consumer (struct g_raid_softc*,TYPE_1__*) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 

__attribute__((used)) static void
g_raid_disk_done_request(struct bio *bp)
{
	struct g_raid_softc *sc;
	struct g_raid_disk *disk;
	struct g_raid_subdisk *sd;
	struct g_raid_volume *vol;

	g_topology_assert_not();

	G_RAID_LOGREQ(3, bp, "Disk request done: %d.", bp->bio_error);
	sd = bp->bio_caller1;
	sc = sd->sd_softc;
	vol = sd->sd_volume;
	if (bp->bio_from != NULL) {
		bp->bio_from->index--;
		disk = bp->bio_from->private;
		if (disk == NULL)
			g_raid_kill_consumer(sc, bp->bio_from);
	}
	bp->bio_offset -= sd->sd_offset;

	G_RAID_TR_IODONE(vol->v_tr, sd, bp);
}