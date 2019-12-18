#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct g_raid3_softc {int /*<<< orphan*/  sc_inflight; int /*<<< orphan*/  sc_bump_id; int /*<<< orphan*/  sc_state; int /*<<< orphan*/  sc_writes; } ;
struct g_raid3_disk {int d_flags; } ;
struct bio {scalar_t__ bio_cmd; scalar_t__ bio_inbed; scalar_t__ bio_children; int bio_error; int /*<<< orphan*/  bio_pflags; struct g_raid3_disk* bio_caller2; int /*<<< orphan*/  bio_length; int /*<<< orphan*/  bio_completed; TYPE_3__* bio_from; TYPE_2__* bio_to; struct bio* bio_parent; } ;
struct TYPE_6__ {struct g_raid3_disk* private; int /*<<< orphan*/  index; } ;
struct TYPE_5__ {TYPE_1__* geom; } ;
struct TYPE_4__ {struct g_raid3_softc* softc; } ;

/* Variables and functions */
#define  BIO_DELETE 130 
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 int /*<<< orphan*/  G_RAID3_BIO_PFLAG_DEGRADED ; 
 int /*<<< orphan*/  G_RAID3_BIO_PFLAG_NOPARITY ; 
 int /*<<< orphan*/  G_RAID3_BUMP_GENID ; 
 int /*<<< orphan*/  G_RAID3_DEVICE_STATE_COMPLETE ; 
 int G_RAID3_DISK_FLAG_BROKEN ; 
 int /*<<< orphan*/  G_RAID3_DISK_STATE_DISCONNECTED ; 
 int /*<<< orphan*/  G_RAID3_EVENT_DONTWAIT ; 
 struct bio* G_RAID3_HEAD_BIO (struct bio*) ; 
 int /*<<< orphan*/  G_RAID3_LOGREQ (int,struct bio*,char*,...) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bioq_remove (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int) ; 
 int /*<<< orphan*/  g_raid3_destroy_bio (struct g_raid3_softc*,struct bio*) ; 
 int /*<<< orphan*/  g_raid3_disconnect_on_failure ; 
 int /*<<< orphan*/  g_raid3_event_send (struct g_raid3_disk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid3_gather (struct bio*) ; 
 int /*<<< orphan*/  g_raid3_kill_consumer (struct g_raid3_softc*,TYPE_3__*) ; 
 int /*<<< orphan*/  g_raid3_sync_release (struct g_raid3_softc*) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 

__attribute__((used)) static void
g_raid3_regular_request(struct bio *cbp)
{
	struct g_raid3_softc *sc;
	struct g_raid3_disk *disk;
	struct bio *pbp;

	g_topology_assert_not();

	pbp = cbp->bio_parent;
	sc = pbp->bio_to->geom->softc;
	cbp->bio_from->index--;
	if (cbp->bio_cmd == BIO_WRITE)
		sc->sc_writes--;
	disk = cbp->bio_from->private;
	if (disk == NULL) {
		g_topology_lock();
		g_raid3_kill_consumer(sc, cbp->bio_from);
		g_topology_unlock();
	}

	G_RAID3_LOGREQ(3, cbp, "Request finished.");
	pbp->bio_inbed++;
	KASSERT(pbp->bio_inbed <= pbp->bio_children,
	    ("bio_inbed (%u) is bigger than bio_children (%u).", pbp->bio_inbed,
	    pbp->bio_children));
	if (pbp->bio_inbed != pbp->bio_children)
		return;
	switch (pbp->bio_cmd) {
	case BIO_READ:
		g_raid3_gather(pbp);
		break;
	case BIO_WRITE:
	case BIO_DELETE:
	    {
		int error = 0;

		pbp->bio_completed = pbp->bio_length;
		while ((cbp = G_RAID3_HEAD_BIO(pbp)) != NULL) {
			if (cbp->bio_error == 0) {
				g_raid3_destroy_bio(sc, cbp);
				continue;
			}

			if (error == 0)
				error = cbp->bio_error;
			else if (pbp->bio_error == 0) {
				/*
				 * Next failed request, that's too many.
				 */
				pbp->bio_error = error;
			}

			disk = cbp->bio_caller2;
			if (disk == NULL) {
				g_raid3_destroy_bio(sc, cbp);
				continue;
			}

			if ((disk->d_flags & G_RAID3_DISK_FLAG_BROKEN) == 0) {
				disk->d_flags |= G_RAID3_DISK_FLAG_BROKEN;
				G_RAID3_LOGREQ(0, cbp,
				    "Request failed (error=%d).",
				    cbp->bio_error);
			} else {
				G_RAID3_LOGREQ(1, cbp,
				    "Request failed (error=%d).",
				    cbp->bio_error);
			}
			if (g_raid3_disconnect_on_failure &&
			    sc->sc_state == G_RAID3_DEVICE_STATE_COMPLETE) {
				sc->sc_bump_id |= G_RAID3_BUMP_GENID;
				g_raid3_event_send(disk,
				    G_RAID3_DISK_STATE_DISCONNECTED,
				    G_RAID3_EVENT_DONTWAIT);
			}
			g_raid3_destroy_bio(sc, cbp);
		}
		if (pbp->bio_error == 0)
			G_RAID3_LOGREQ(3, pbp, "Request finished.");
		else
			G_RAID3_LOGREQ(0, pbp, "Request failed.");
		pbp->bio_pflags &= ~G_RAID3_BIO_PFLAG_DEGRADED;
		pbp->bio_pflags &= ~G_RAID3_BIO_PFLAG_NOPARITY;
		bioq_remove(&sc->sc_inflight, pbp);
		/* Release delayed sync requests if possible. */
		g_raid3_sync_release(sc);
		g_io_deliver(pbp, pbp->bio_error);
		break;
	    }
	}
}