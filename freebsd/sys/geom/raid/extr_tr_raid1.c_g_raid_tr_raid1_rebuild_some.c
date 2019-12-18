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
struct bio {int /*<<< orphan*/  bio_length; scalar_t__ bio_offset; struct g_raid_subdisk* bio_caller1; int /*<<< orphan*/  bio_cflags; int /*<<< orphan*/  bio_cmd; int /*<<< orphan*/  bio_data; } ;
struct g_raid_tr_raid1_object {int trso_flags; int /*<<< orphan*/  trso_buffer; struct bio trso_bio; struct g_raid_subdisk* trso_failed_sd; } ;
struct g_raid_tr_object {int dummy; } ;
struct g_raid_subdisk {int /*<<< orphan*/  sd_volume; scalar_t__ sd_rebuild_pos; scalar_t__ sd_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_READ ; 
 int /*<<< orphan*/  G_RAID_BIO_FLAG_SYNC ; 
 int /*<<< orphan*/  G_RAID_SUBDISK_S_ACTIVE ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int TR_RAID1_F_DOING_SOME ; 
 int TR_RAID1_F_LOCKED ; 
 int /*<<< orphan*/  g_raid1_rebuild_slab ; 
 struct g_raid_subdisk* g_raid_get_subdisk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid_lock_range (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  g_raid_tr_raid1_rebuild_abort (struct g_raid_tr_object*) ; 
 int /*<<< orphan*/  memset (struct bio*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
g_raid_tr_raid1_rebuild_some(struct g_raid_tr_object *tr)
{
	struct g_raid_tr_raid1_object *trs;
	struct g_raid_subdisk *sd, *good_sd;
	struct bio *bp;

	trs = (struct g_raid_tr_raid1_object *)tr;
	if (trs->trso_flags & TR_RAID1_F_DOING_SOME)
		return;
	sd = trs->trso_failed_sd;
	good_sd = g_raid_get_subdisk(sd->sd_volume, G_RAID_SUBDISK_S_ACTIVE);
	if (good_sd == NULL) {
		g_raid_tr_raid1_rebuild_abort(tr);
		return;
	}
	bp = &trs->trso_bio;
	memset(bp, 0, sizeof(*bp));
	bp->bio_offset = sd->sd_rebuild_pos;
	bp->bio_length = MIN(g_raid1_rebuild_slab,
	    sd->sd_size - sd->sd_rebuild_pos);
	bp->bio_data = trs->trso_buffer;
	bp->bio_cmd = BIO_READ;
	bp->bio_cflags = G_RAID_BIO_FLAG_SYNC;
	bp->bio_caller1 = good_sd;
	trs->trso_flags |= TR_RAID1_F_DOING_SOME;
	trs->trso_flags |= TR_RAID1_F_LOCKED;
	g_raid_lock_range(sd->sd_volume,	/* Lock callback starts I/O */
	   bp->bio_offset, bp->bio_length, NULL, bp);
}