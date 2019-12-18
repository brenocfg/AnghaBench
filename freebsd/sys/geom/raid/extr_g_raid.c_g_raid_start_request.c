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
struct g_raid_volume {int /*<<< orphan*/  v_tr; int /*<<< orphan*/  v_inflight; int /*<<< orphan*/  v_writes; int /*<<< orphan*/  v_dirty; int /*<<< orphan*/  v_locked; } ;
struct g_raid_softc {int /*<<< orphan*/  sc_lock; } ;
struct bio {int bio_cflags; scalar_t__ bio_cmd; TYPE_2__* bio_to; } ;
struct TYPE_4__ {struct g_raid_volume* private; TYPE_1__* geom; } ;
struct TYPE_3__ {struct g_raid_softc* softc; } ;

/* Variables and functions */
 scalar_t__ BIO_DELETE ; 
 scalar_t__ BIO_WRITE ; 
 int G_RAID_BIO_FLAG_SPECIAL ; 
 int /*<<< orphan*/  G_RAID_LOGREQ (int,struct bio*,char*) ; 
 int /*<<< orphan*/  G_RAID_TR_IOSTART (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  SX_LOCKED ; 
 int /*<<< orphan*/  bioq_insert_tail (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  g_raid_dirty (struct g_raid_volume*) ; 
 scalar_t__ g_raid_is_in_locked_range (struct g_raid_volume*,struct bio*) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_raid_start_request(struct bio *bp)
{
	struct g_raid_softc *sc;
	struct g_raid_volume *vol;

	sc = bp->bio_to->geom->softc;
	sx_assert(&sc->sc_lock, SX_LOCKED);
	vol = bp->bio_to->private;

	/*
	 * Check to see if this item is in a locked range.  If so,
	 * queue it to our locked queue and return.  We'll requeue
	 * it when the range is unlocked.  Internal I/O for the
	 * rebuild/rescan/recovery process is excluded from this
	 * check so we can actually do the recovery.
	 */
	if (!(bp->bio_cflags & G_RAID_BIO_FLAG_SPECIAL) &&
	    g_raid_is_in_locked_range(vol, bp)) {
		G_RAID_LOGREQ(3, bp, "Defer request.");
		bioq_insert_tail(&vol->v_locked, bp);
		return;
	}

	/*
	 * If we're actually going to do the write/delete, then
	 * update the idle stats for the volume.
	 */
	if (bp->bio_cmd == BIO_WRITE || bp->bio_cmd == BIO_DELETE) {
		if (!vol->v_dirty)
			g_raid_dirty(vol);
		vol->v_writes++;
	}

	/*
	 * Put request onto inflight queue, so we can check if new
	 * synchronization requests don't collide with it.  Then tell
	 * the transformation layer to start the I/O.
	 */
	bioq_insert_tail(&vol->v_inflight, bp);
	G_RAID_LOGREQ(4, bp, "Request started");
	G_RAID_TR_IOSTART(vol->v_tr, bp);
}