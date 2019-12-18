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
struct g_raid_volume {int /*<<< orphan*/  v_last_done; scalar_t__ v_pending_lock; int /*<<< orphan*/  v_inflight; int /*<<< orphan*/  v_last_write; int /*<<< orphan*/  v_writes; } ;
struct g_raid_softc {int /*<<< orphan*/  sc_lock; } ;
struct bio {scalar_t__ bio_cmd; TYPE_2__* bio_to; } ;
struct TYPE_4__ {struct g_raid_volume* private; TYPE_1__* geom; } ;
struct TYPE_3__ {struct g_raid_softc* softc; } ;

/* Variables and functions */
 scalar_t__ BIO_DELETE ; 
 scalar_t__ BIO_WRITE ; 
 int /*<<< orphan*/  G_RAID_LOGREQ (int,struct bio*,char*,int) ; 
 int /*<<< orphan*/  SX_LOCKED ; 
 int /*<<< orphan*/  bioq_remove (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int) ; 
 int /*<<< orphan*/  g_raid_finish_with_locked_ranges (struct g_raid_volume*,struct bio*) ; 
 scalar_t__ g_raid_is_in_locked_range (struct g_raid_volume*,struct bio*) ; 
 int /*<<< orphan*/  getmicrouptime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_uptime ; 

void
g_raid_iodone(struct bio *bp, int error)
{
	struct g_raid_softc *sc;
	struct g_raid_volume *vol;

	sc = bp->bio_to->geom->softc;
	sx_assert(&sc->sc_lock, SX_LOCKED);
	vol = bp->bio_to->private;
	G_RAID_LOGREQ(3, bp, "Request done: %d.", error);

	/* Update stats if we done write/delete. */
	if (bp->bio_cmd == BIO_WRITE || bp->bio_cmd == BIO_DELETE) {
		vol->v_writes--;
		vol->v_last_write = time_uptime;
	}

	bioq_remove(&vol->v_inflight, bp);
	if (vol->v_pending_lock && g_raid_is_in_locked_range(vol, bp))
		g_raid_finish_with_locked_ranges(vol, bp);
	getmicrouptime(&vol->v_last_done);
	g_io_deliver(bp, error);
}