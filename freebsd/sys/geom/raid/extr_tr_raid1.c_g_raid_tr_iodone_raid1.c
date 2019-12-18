#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct g_raid_volume {int /*<<< orphan*/  v_softc; } ;
struct g_raid_tr_raid1_object {scalar_t__ trso_type; int trso_flags; scalar_t__ trso_meta_update; scalar_t__ trso_recover_slabs; scalar_t__ trso_stopping; struct g_raid_subdisk* trso_failed_sd; } ;
struct g_raid_tr_object {struct g_raid_volume* tro_volume; } ;
struct g_raid_subdisk {scalar_t__ sd_rebuild_pos; scalar_t__ sd_size; int sd_pos; TYPE_1__* sd_disk; int /*<<< orphan*/  sd_softc; int /*<<< orphan*/  sd_volume; int /*<<< orphan*/  sd_recovery; } ;
struct bio {int bio_cflags; scalar_t__ bio_cmd; int bio_error; scalar_t__ bio_length; int bio_inbed; int bio_children; int bio_pflags; scalar_t__ bio_completed; int /*<<< orphan*/  bio_offset; struct g_raid_subdisk* bio_driver1; struct g_raid_subdisk* bio_caller1; int /*<<< orphan*/  bio_driver2; struct bio* bio_parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  d_read_errs; } ;

/* Variables and functions */
 scalar_t__ BIO_READ ; 
 scalar_t__ BIO_WRITE ; 
 int G_RAID_BIO_FLAG_LOCKED ; 
 int G_RAID_BIO_FLAG_REMAP ; 
 int G_RAID_BIO_FLAG_SYNC ; 
 int /*<<< orphan*/  G_RAID_LOGREQ (int,struct bio*,char*,...) ; 
 int TR_RAID1_F_ABORT ; 
 int TR_RAID1_F_DOING_SOME ; 
 int TR_RAID1_F_LOCKED ; 
 scalar_t__ TR_RAID1_REBUILD ; 
 scalar_t__ TR_RAID1_RESYNC ; 
 struct bio* g_clone_bio (struct bio*) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 scalar_t__ g_raid1_rebuild_meta_update ; 
 int /*<<< orphan*/  g_raid_iodone (struct bio*,int) ; 
 int /*<<< orphan*/  g_raid_lock_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct bio*,struct bio*) ; 
 int /*<<< orphan*/  g_raid_read_err_thresh ; 
 int /*<<< orphan*/  g_raid_subdisk_iostart (struct g_raid_subdisk*,struct bio*) ; 
 int /*<<< orphan*/  g_raid_tr_raid1_fail_disk (int /*<<< orphan*/ ,struct g_raid_subdisk*,TYPE_1__*) ; 
 int /*<<< orphan*/  g_raid_tr_raid1_rebuild_abort (struct g_raid_tr_object*) ; 
 int /*<<< orphan*/  g_raid_tr_raid1_rebuild_finish (struct g_raid_tr_object*) ; 
 int /*<<< orphan*/  g_raid_tr_raid1_rebuild_some (struct g_raid_tr_object*) ; 
 struct g_raid_subdisk* g_raid_tr_raid1_select_read_disk (struct g_raid_volume*,struct bio*,uintptr_t) ; 
 int /*<<< orphan*/  g_raid_unlock_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  g_raid_write_metadata (int /*<<< orphan*/ ,struct g_raid_volume*,struct g_raid_subdisk*,TYPE_1__*) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
g_raid_tr_iodone_raid1(struct g_raid_tr_object *tr,
    struct g_raid_subdisk *sd, struct bio *bp)
{
	struct bio *cbp;
	struct g_raid_subdisk *nsd;
	struct g_raid_volume *vol;
	struct bio *pbp;
	struct g_raid_tr_raid1_object *trs;
	uintptr_t *mask;
	int error, do_write;

	trs = (struct g_raid_tr_raid1_object *)tr;
	vol = tr->tro_volume;
	if (bp->bio_cflags & G_RAID_BIO_FLAG_SYNC) {
		/*
		 * This operation is part of a rebuild or resync operation.
		 * See what work just got done, then schedule the next bit of
		 * work, if any.  Rebuild/resync is done a little bit at a
		 * time.  Either when a timeout happens, or after we get a
		 * bunch of I/Os to the disk (to make sure an active system
		 * will complete in a sane amount of time).
		 *
		 * We are setup to do differing amounts of work for each of
		 * these cases.  so long as the slabs is smallish (less than
		 * 50 or so, I'd guess, but that's just a WAG), we shouldn't
		 * have any bio starvation issues.  For active disks, we do
		 * 5MB of data, for inactive ones, we do 50MB.
		 */
		if (trs->trso_type == TR_RAID1_REBUILD) {
			if (bp->bio_cmd == BIO_READ) {

				/* Immediately abort rebuild, if requested. */
				if (trs->trso_flags & TR_RAID1_F_ABORT) {
					trs->trso_flags &= ~TR_RAID1_F_DOING_SOME;
					g_raid_tr_raid1_rebuild_abort(tr);
					return;
				}

				/* On read error, skip and cross fingers. */
				if (bp->bio_error != 0) {
					G_RAID_LOGREQ(0, bp,
					    "Read error during rebuild (%d), "
					    "possible data loss!",
					    bp->bio_error);
					goto rebuild_round_done;
				}

				/*
				 * The read operation finished, queue the
				 * write and get out.
				 */
				G_RAID_LOGREQ(4, bp, "rebuild read done. %d",
				    bp->bio_error);
				bp->bio_cmd = BIO_WRITE;
				bp->bio_cflags = G_RAID_BIO_FLAG_SYNC;
				G_RAID_LOGREQ(4, bp, "Queueing rebuild write.");
				g_raid_subdisk_iostart(trs->trso_failed_sd, bp);
			} else {
				/*
				 * The write operation just finished.  Do
				 * another.  We keep cloning the master bio
				 * since it has the right buffers allocated to
				 * it.
				 */
				G_RAID_LOGREQ(4, bp,
				    "rebuild write done. Error %d",
				    bp->bio_error);
				nsd = trs->trso_failed_sd;
				if (bp->bio_error != 0 ||
				    trs->trso_flags & TR_RAID1_F_ABORT) {
					if ((trs->trso_flags &
					    TR_RAID1_F_ABORT) == 0) {
						g_raid_tr_raid1_fail_disk(sd->sd_softc,
						    nsd, nsd->sd_disk);
					}
					trs->trso_flags &= ~TR_RAID1_F_DOING_SOME;
					g_raid_tr_raid1_rebuild_abort(tr);
					return;
				}
rebuild_round_done:
				nsd = trs->trso_failed_sd;
				trs->trso_flags &= ~TR_RAID1_F_LOCKED;
				g_raid_unlock_range(sd->sd_volume,
				    bp->bio_offset, bp->bio_length);
				nsd->sd_rebuild_pos += bp->bio_length;
				if (nsd->sd_rebuild_pos >= nsd->sd_size) {
					g_raid_tr_raid1_rebuild_finish(tr);
					return;
				}

				/* Abort rebuild if we are stopping */
				if (trs->trso_stopping) {
					trs->trso_flags &= ~TR_RAID1_F_DOING_SOME;
					g_raid_tr_raid1_rebuild_abort(tr);
					return;
				}

				if (--trs->trso_meta_update <= 0) {
					g_raid_write_metadata(vol->v_softc,
					    vol, nsd, nsd->sd_disk);
					trs->trso_meta_update =
					    g_raid1_rebuild_meta_update;
				}
				trs->trso_flags &= ~TR_RAID1_F_DOING_SOME;
				if (--trs->trso_recover_slabs <= 0)
					return;
				g_raid_tr_raid1_rebuild_some(tr);
			}
		} else if (trs->trso_type == TR_RAID1_RESYNC) {
			/*
			 * read good sd, read bad sd in parallel.  when both
			 * done, compare the buffers.  write good to the bad
			 * if different.  do the next bit of work.
			 */
			panic("Somehow, we think we're doing a resync");
		}
		return;
	}
	pbp = bp->bio_parent;
	pbp->bio_inbed++;
	if (bp->bio_cmd == BIO_READ && bp->bio_error != 0) {
		/*
		 * Read failed on first drive.  Retry the read error on
		 * another disk drive, if available, before erroring out the
		 * read.
		 */
		sd->sd_disk->d_read_errs++;
		G_RAID_LOGREQ(0, bp,
		    "Read error (%d), %d read errors total",
		    bp->bio_error, sd->sd_disk->d_read_errs);

		/*
		 * If there are too many read errors, we move to degraded.
		 * XXX Do we want to FAIL the drive (eg, make the user redo
		 * everything to get it back in sync), or just degrade the
		 * drive, which kicks off a resync?
		 */
		do_write = 1;
		if (sd->sd_disk->d_read_errs > g_raid_read_err_thresh) {
			g_raid_tr_raid1_fail_disk(sd->sd_softc, sd, sd->sd_disk);
			if (pbp->bio_children == 1)
				do_write = 0;
		}

		/*
		 * Find the other disk, and try to do the I/O to it.
		 */
		mask = (uintptr_t *)(&pbp->bio_driver2);
		if (pbp->bio_children == 1) {
			/* Save original subdisk. */
			pbp->bio_driver1 = do_write ? sd : NULL;
			*mask = 0;
		}
		*mask |= 1 << sd->sd_pos;
		nsd = g_raid_tr_raid1_select_read_disk(vol, pbp, *mask);
		if (nsd != NULL && (cbp = g_clone_bio(pbp)) != NULL) {
			g_destroy_bio(bp);
			G_RAID_LOGREQ(2, cbp, "Retrying read from %d",
			    nsd->sd_pos);
			if (pbp->bio_children == 2 && do_write) {
				sd->sd_recovery++;
				cbp->bio_caller1 = nsd;
				pbp->bio_pflags = G_RAID_BIO_FLAG_LOCKED;
				/* Lock callback starts I/O */
				g_raid_lock_range(sd->sd_volume,
				    cbp->bio_offset, cbp->bio_length, pbp, cbp);
			} else {
				g_raid_subdisk_iostart(nsd, cbp);
			}
			return;
		}
		/*
		 * We can't retry.  Return the original error by falling
		 * through.  This will happen when there's only one good disk.
		 * We don't need to fail the raid, since its actual state is
		 * based on the state of the subdisks.
		 */
		G_RAID_LOGREQ(2, bp, "Couldn't retry read, failing it");
	}
	if (bp->bio_cmd == BIO_READ &&
	    bp->bio_error == 0 &&
	    pbp->bio_children > 1 &&
	    pbp->bio_driver1 != NULL) {
		/*
		 * If it was a read, and bio_children is >1, then we just
		 * recovered the data from the second drive.  We should try to
		 * write that data to the first drive if sector remapping is
		 * enabled.  A write should put the data in a new place on the
		 * disk, remapping the bad sector.  Do we need to do that by
		 * queueing a request to the main worker thread?  It doesn't
		 * affect the return code of this current read, and can be
		 * done at our leisure.  However, to make the code simpler, it
		 * is done synchronously.
		 */
		G_RAID_LOGREQ(3, bp, "Recovered data from other drive");
		cbp = g_clone_bio(pbp);
		if (cbp != NULL) {
			g_destroy_bio(bp);
			cbp->bio_cmd = BIO_WRITE;
			cbp->bio_cflags = G_RAID_BIO_FLAG_REMAP;
			G_RAID_LOGREQ(2, cbp,
			    "Attempting bad sector remap on failing drive.");
			g_raid_subdisk_iostart(pbp->bio_driver1, cbp);
			return;
		}
	}
	if (pbp->bio_pflags & G_RAID_BIO_FLAG_LOCKED) {
		/*
		 * We're done with a recovery, mark the range as unlocked.
		 * For any write errors, we aggressively fail the disk since
		 * there was both a READ and a WRITE error at this location.
		 * Both types of errors generally indicates the drive is on
		 * the verge of total failure anyway.  Better to stop trusting
		 * it now.  However, we need to reset error to 0 in that case
		 * because we're not failing the original I/O which succeeded.
		 */
		if (bp->bio_cmd == BIO_WRITE && bp->bio_error) {
			G_RAID_LOGREQ(0, bp, "Remap write failed: "
			    "failing subdisk.");
			g_raid_tr_raid1_fail_disk(sd->sd_softc, sd, sd->sd_disk);
			bp->bio_error = 0;
		}
		if (pbp->bio_driver1 != NULL) {
			((struct g_raid_subdisk *)pbp->bio_driver1)
			    ->sd_recovery--;
		}
		G_RAID_LOGREQ(2, bp, "REMAP done %d.", bp->bio_error);
		g_raid_unlock_range(sd->sd_volume, bp->bio_offset,
		    bp->bio_length);
	}
	if (pbp->bio_cmd != BIO_READ) {
		if (pbp->bio_inbed == 1 || pbp->bio_error != 0)
			pbp->bio_error = bp->bio_error;
		if (pbp->bio_cmd == BIO_WRITE && bp->bio_error != 0) {
			G_RAID_LOGREQ(0, bp, "Write failed: failing subdisk.");
			g_raid_tr_raid1_fail_disk(sd->sd_softc, sd, sd->sd_disk);
		}
		error = pbp->bio_error;
	} else
		error = bp->bio_error;
	g_destroy_bio(bp);
	if (pbp->bio_children == pbp->bio_inbed) {
		pbp->bio_completed = pbp->bio_length;
		g_raid_iodone(pbp, error);
	}
}