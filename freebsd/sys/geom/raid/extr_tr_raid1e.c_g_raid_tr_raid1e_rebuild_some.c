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
struct g_raid_volume {int v_disks_count; scalar_t__ v_strip_size; int /*<<< orphan*/ * v_subdisks; struct g_raid_softc* v_softc; } ;
struct bio {int /*<<< orphan*/ * bio_caller1; int /*<<< orphan*/  bio_cflags; int /*<<< orphan*/  bio_cmd; int /*<<< orphan*/  bio_data; scalar_t__ bio_length; scalar_t__ bio_offset; } ;
struct g_raid_tr_raid1e_object {int trso_flags; scalar_t__ trso_lock_len; scalar_t__ trso_lock_pos; int /*<<< orphan*/  trso_buffer; struct bio trso_bio; struct g_raid_subdisk* trso_failed_sd; } ;
struct g_raid_tr_object {struct g_raid_volume* tro_volume; } ;
struct g_raid_subdisk {scalar_t__ sd_rebuild_pos; scalar_t__ sd_size; int /*<<< orphan*/  sd_volume; int /*<<< orphan*/  sd_pos; } ;
struct g_raid_softc {int dummy; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_READ ; 
 int /*<<< orphan*/  G_RAID_BIO_FLAG_SYNC ; 
 int /*<<< orphan*/  G_RAID_DEBUG1 (int,struct g_raid_softc*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  G_RAID_LOGREQ (int,struct bio*,char*) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int N ; 
 int /*<<< orphan*/  P2V (struct g_raid_volume*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int*) ; 
 int TR_RAID1E_F_DOING_SOME ; 
 int TR_RAID1E_F_LOCKED ; 
 int /*<<< orphan*/  V2P (struct g_raid_volume*,scalar_t__,int*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ g_raid1e_rebuild_slab ; 
 int /*<<< orphan*/  g_raid_lock_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  g_raid_tr_raid1e_rebuild_abort (struct g_raid_tr_object*) ; 
 int /*<<< orphan*/  g_raid_tr_raid1e_rebuild_finish (struct g_raid_tr_object*) ; 
 int g_raid_tr_raid1e_select_read_disk (struct g_raid_volume*,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bio*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
g_raid_tr_raid1e_rebuild_some(struct g_raid_tr_object *tr)
{
	struct g_raid_tr_raid1e_object *trs;
	struct g_raid_softc *sc;
	struct g_raid_volume *vol;
	struct g_raid_subdisk *sd;
	struct bio *bp;
	off_t len, virtual, vend, offset, start;
	int disk, copy, best;

	trs = (struct g_raid_tr_raid1e_object *)tr;
	if (trs->trso_flags & TR_RAID1E_F_DOING_SOME)
		return;
	vol = tr->tro_volume;
	sc = vol->v_softc;
	sd = trs->trso_failed_sd;

	while (1) {
		if (sd->sd_rebuild_pos >= sd->sd_size) {
			g_raid_tr_raid1e_rebuild_finish(tr);
			return;
		}
		/* Get virtual offset from physical rebuild position. */
		P2V(vol, sd->sd_pos, sd->sd_rebuild_pos, &virtual, &copy);
		/* Get physical offset back to get first stripe position. */
		V2P(vol, virtual, &disk, &offset, &start);
		/* Calculate contignous data length. */
		len = MIN(g_raid1e_rebuild_slab,
		    sd->sd_size - sd->sd_rebuild_pos);
		if ((vol->v_disks_count % N) != 0)
			len = MIN(len, vol->v_strip_size - start);
		/* Find disk with most accurate data. */
		best = g_raid_tr_raid1e_select_read_disk(vol, disk,
		    offset + start, len, 0);
		if (best < 0) {
			/* There is no any valid disk. */
			g_raid_tr_raid1e_rebuild_abort(tr);
			return;
		} else if (best != copy) {
			/* Some other disk has better data. */
			break;
		}
		/* We have the most accurate data. Skip the range. */
		G_RAID_DEBUG1(3, sc, "Skipping rebuild for range %ju - %ju",
		    sd->sd_rebuild_pos, sd->sd_rebuild_pos + len);
		sd->sd_rebuild_pos += len;
	}

	bp = &trs->trso_bio;
	memset(bp, 0, sizeof(*bp));
	bp->bio_offset = offset + start +
	    ((disk + best >= vol->v_disks_count) ? vol->v_strip_size : 0);
	bp->bio_length = len;
	bp->bio_data = trs->trso_buffer;
	bp->bio_cmd = BIO_READ;
	bp->bio_cflags = G_RAID_BIO_FLAG_SYNC;
	bp->bio_caller1 = &vol->v_subdisks[(disk + best) % vol->v_disks_count];
	G_RAID_LOGREQ(3, bp, "Queueing rebuild read");
	/*
	 * If we are crossing stripe boundary, correct affected virtual
	 * range we should lock.
	 */
	if (start + len > vol->v_strip_size) {
		P2V(vol, sd->sd_pos, sd->sd_rebuild_pos + len, &vend, &copy);
		len = vend - virtual;
	}
	trs->trso_flags |= TR_RAID1E_F_DOING_SOME;
	trs->trso_flags |= TR_RAID1E_F_LOCKED;
	trs->trso_lock_pos = virtual;
	trs->trso_lock_len = len;
	/* Lock callback starts I/O */
	g_raid_lock_range(sd->sd_volume, virtual, len, NULL, bp);
}