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
struct g_raid_volume {int v_disks_count; struct g_raid_subdisk* v_subdisks; } ;
struct g_raid_tr_object {struct g_raid_volume* tro_volume; } ;
struct g_raid_subdisk {int sd_state; int /*<<< orphan*/  sd_rebuild_pos; } ;
struct bio_queue_head {int dummy; } ;
struct bio {scalar_t__ bio_error; struct g_raid_subdisk* bio_caller1; int /*<<< orphan*/  bio_offset; } ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
#define  G_RAID_SUBDISK_S_ACTIVE 131 
#define  G_RAID_SUBDISK_S_REBUILD 130 
#define  G_RAID_SUBDISK_S_RESYNC 129 
#define  G_RAID_SUBDISK_S_STALE 128 
 int /*<<< orphan*/  bioq_init (struct bio_queue_head*) ; 
 int /*<<< orphan*/  bioq_insert_tail (struct bio_queue_head*,struct bio*) ; 
 struct bio* bioq_takefirst (struct bio_queue_head*) ; 
 struct bio* g_clone_bio (struct bio*) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_raid_iodone (struct bio*,scalar_t__) ; 
 int /*<<< orphan*/  g_raid_subdisk_iostart (struct g_raid_subdisk*,struct bio*) ; 

__attribute__((used)) static void
g_raid_tr_iostart_raid1_write(struct g_raid_tr_object *tr, struct bio *bp)
{
	struct g_raid_volume *vol;
	struct g_raid_subdisk *sd;
	struct bio_queue_head queue;
	struct bio *cbp;
	int i;

	vol = tr->tro_volume;

	/*
	 * Allocate all bios before sending any request, so we can return
	 * ENOMEM in nice and clean way.
	 */
	bioq_init(&queue);
	for (i = 0; i < vol->v_disks_count; i++) {
		sd = &vol->v_subdisks[i];
		switch (sd->sd_state) {
		case G_RAID_SUBDISK_S_ACTIVE:
			break;
		case G_RAID_SUBDISK_S_REBUILD:
			/*
			 * When rebuilding, only part of this subdisk is
			 * writable, the rest will be written as part of the
			 * that process.
			 */
			if (bp->bio_offset >= sd->sd_rebuild_pos)
				continue;
			break;
		case G_RAID_SUBDISK_S_STALE:
		case G_RAID_SUBDISK_S_RESYNC:
			/*
			 * Resyncing still writes on the theory that the
			 * resync'd disk is very close and writing it will
			 * keep it that way better if we keep up while
			 * resyncing.
			 */
			break;
		default:
			continue;
		}
		cbp = g_clone_bio(bp);
		if (cbp == NULL)
			goto failure;
		cbp->bio_caller1 = sd;
		bioq_insert_tail(&queue, cbp);
	}
	while ((cbp = bioq_takefirst(&queue)) != NULL) {
		sd = cbp->bio_caller1;
		cbp->bio_caller1 = NULL;
		g_raid_subdisk_iostart(sd, cbp);
	}
	return;
failure:
	while ((cbp = bioq_takefirst(&queue)) != NULL)
		g_destroy_bio(cbp);
	if (bp->bio_error == 0)
		bp->bio_error = ENOMEM;
	g_raid_iodone(bp, bp->bio_error);
}