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
typedef  int /*<<< orphan*/  time_t ;
struct g_provider {int /*<<< orphan*/  sectorsize; int /*<<< orphan*/  mediasize; } ;
struct g_journal_softc {int sc_flags; scalar_t__ sc_current_count; scalar_t__ sc_flush_in_progress; scalar_t__ sc_copy_in_progress; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_back_queue; int /*<<< orphan*/  sc_regular_queue; int /*<<< orphan*/ * sc_worker; int /*<<< orphan*/ * sc_journal_copying; int /*<<< orphan*/ * sc_rootmount; int /*<<< orphan*/  sc_sectorsize; int /*<<< orphan*/  sc_mediasize; int /*<<< orphan*/ * sc_name; struct g_geom* sc_geom; TYPE_2__* sc_dconsumer; int /*<<< orphan*/  sc_bio_flush; TYPE_2__* sc_jconsumer; } ;
struct g_geom {int /*<<< orphan*/ * name; } ;
struct bio {int bio_cflags; scalar_t__ bio_cmd; scalar_t__ bio_length; scalar_t__ bio_offset; } ;
struct TYPE_4__ {TYPE_1__* provider; } ;
struct TYPE_3__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
#define  BIO_READ 133 
#define  BIO_WRITE 132 
 int GJF_DEVICE_CLEAN ; 
 int GJF_DEVICE_DESTROY ; 
 int GJF_DEVICE_SWITCH ; 
#define  GJ_BIO_COPY 131 
#define  GJ_BIO_JOURNAL 130 
 int GJ_BIO_MASK ; 
#define  GJ_BIO_READ 129 
#define  GJ_BIO_REGULAR 128 
 int /*<<< orphan*/  GJ_DEBUG (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GJ_FLUSH_DATA ; 
 int /*<<< orphan*/  GJ_FLUSH_JOURNAL ; 
 int /*<<< orphan*/  GJ_LOGREQ (int,struct bio*,char*) ; 
 int /*<<< orphan*/  PRIBIO ; 
 struct bio* bioq_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioq_remove (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  g_error_provider (struct g_provider*,int /*<<< orphan*/ ) ; 
 scalar_t__ g_io_flush (TYPE_2__*) ; 
 int /*<<< orphan*/  g_journal_add_request (struct g_journal_softc*,struct bio*) ; 
 int /*<<< orphan*/  g_journal_copy_read_done (struct bio*) ; 
 int /*<<< orphan*/  g_journal_copy_send (struct g_journal_softc*) ; 
 int /*<<< orphan*/  g_journal_copy_write_done (struct bio*) ; 
 int /*<<< orphan*/  g_journal_flush (struct g_journal_softc*) ; 
 int /*<<< orphan*/  g_journal_flush_done (struct bio*) ; 
 int /*<<< orphan*/  g_journal_flush_send (struct g_journal_softc*) ; 
 int /*<<< orphan*/  g_journal_initialize (struct g_journal_softc*) ; 
 int /*<<< orphan*/  g_journal_read (struct g_journal_softc*,struct bio*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  g_journal_switch (struct g_journal_softc*) ; 
 int /*<<< orphan*/  g_journal_sync (struct g_journal_softc*) ; 
 int /*<<< orphan*/  g_journal_wait (struct g_journal_softc*,int /*<<< orphan*/ ) ; 
 struct g_provider* g_new_providerf (struct g_geom*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  root_mount_rel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_prio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_second ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
g_journal_worker(void *arg)
{
	struct g_journal_softc *sc;
	struct g_geom *gp;
	struct g_provider *pp;
	struct bio *bp;
	time_t last_write;
	int type;

	thread_lock(curthread);
	sched_prio(curthread, PRIBIO);
	thread_unlock(curthread);

	sc = arg;
	type = 0;	/* gcc */

	if (sc->sc_flags & GJF_DEVICE_CLEAN) {
		GJ_DEBUG(0, "Journal %s clean.", sc->sc_name);
		g_journal_initialize(sc);
	} else {
		g_journal_sync(sc);
	}
	/*
	 * Check if we can use BIO_FLUSH.
	 */
	sc->sc_bio_flush = 0;
	if (g_io_flush(sc->sc_jconsumer) == 0) {
		sc->sc_bio_flush |= GJ_FLUSH_JOURNAL;
		GJ_DEBUG(1, "BIO_FLUSH supported by %s.",
		    sc->sc_jconsumer->provider->name);
	} else {
		GJ_DEBUG(0, "BIO_FLUSH not supported by %s.",
		    sc->sc_jconsumer->provider->name);
	}
	if (sc->sc_jconsumer != sc->sc_dconsumer) {
		if (g_io_flush(sc->sc_dconsumer) == 0) {
			sc->sc_bio_flush |= GJ_FLUSH_DATA;
			GJ_DEBUG(1, "BIO_FLUSH supported by %s.",
			    sc->sc_dconsumer->provider->name);
		} else {
			GJ_DEBUG(0, "BIO_FLUSH not supported by %s.",
			    sc->sc_dconsumer->provider->name);
		}
	}

	gp = sc->sc_geom;
	g_topology_lock();
	pp = g_new_providerf(gp, "%s.journal", sc->sc_name);
	pp->mediasize = sc->sc_mediasize;
	/*
	 * There could be a problem when data provider and journal providers
	 * have different sectorsize, but such scenario is prevented on journal
	 * creation.
	 */
	pp->sectorsize = sc->sc_sectorsize;
	g_error_provider(pp, 0);
	g_topology_unlock();
	last_write = time_second;

	if (sc->sc_rootmount != NULL) {
		GJ_DEBUG(1, "root_mount_rel %p", sc->sc_rootmount);
		root_mount_rel(sc->sc_rootmount);
		sc->sc_rootmount = NULL;
	}

	for (;;) {
		/* Get first request from the queue. */
		mtx_lock(&sc->sc_mtx);
		bp = bioq_first(&sc->sc_back_queue);
		if (bp != NULL)
			type = (bp->bio_cflags & GJ_BIO_MASK);
		if (bp == NULL) {
			bp = bioq_first(&sc->sc_regular_queue);
			if (bp != NULL)
				type = GJ_BIO_REGULAR;
		}
		if (bp == NULL) {
try_switch:
			if ((sc->sc_flags & GJF_DEVICE_SWITCH) ||
			    (sc->sc_flags & GJF_DEVICE_DESTROY)) {
				if (sc->sc_current_count > 0) {
					mtx_unlock(&sc->sc_mtx);
					g_journal_flush(sc);
					g_journal_flush_send(sc);
					continue;
				}
				if (sc->sc_flush_in_progress > 0)
					goto sleep;
				if (sc->sc_copy_in_progress > 0)
					goto sleep;
			}
			if (sc->sc_flags & GJF_DEVICE_SWITCH) {
				mtx_unlock(&sc->sc_mtx);
				g_journal_switch(sc);
				wakeup(&sc->sc_journal_copying);
				continue;
			}
			if (sc->sc_flags & GJF_DEVICE_DESTROY) {
				GJ_DEBUG(1, "Shutting down worker "
				    "thread for %s.", gp->name);
				sc->sc_worker = NULL;
				wakeup(&sc->sc_worker);
				mtx_unlock(&sc->sc_mtx);
				kproc_exit(0);
			}
sleep:
			g_journal_wait(sc, last_write);
			continue;
		}
		/*
		 * If we're in switch process, we need to delay all new
		 * write requests until its done.
		 */
		if ((sc->sc_flags & GJF_DEVICE_SWITCH) &&
		    type == GJ_BIO_REGULAR && bp->bio_cmd == BIO_WRITE) {
			GJ_LOGREQ(2, bp, "WRITE on SWITCH");
			goto try_switch;
		}
		if (type == GJ_BIO_REGULAR)
			bioq_remove(&sc->sc_regular_queue, bp);
		else
			bioq_remove(&sc->sc_back_queue, bp);
		mtx_unlock(&sc->sc_mtx);
		switch (type) {
		case GJ_BIO_REGULAR:
			/* Regular request. */
			switch (bp->bio_cmd) {
			case BIO_READ:
				g_journal_read(sc, bp, bp->bio_offset,
				    bp->bio_offset + bp->bio_length);
				break;
			case BIO_WRITE:
				last_write = time_second;
				g_journal_add_request(sc, bp);
				g_journal_flush_send(sc);
				break;
			default:
				panic("Invalid bio_cmd (%d).", bp->bio_cmd);
			}
			break;
		case GJ_BIO_COPY:
			switch (bp->bio_cmd) {
			case BIO_READ:
				if (g_journal_copy_read_done(bp))
					g_journal_copy_send(sc);
				break;
			case BIO_WRITE:
				g_journal_copy_write_done(bp);
				g_journal_copy_send(sc);
				break;
			default:
				panic("Invalid bio_cmd (%d).", bp->bio_cmd);
			}
			break;
		case GJ_BIO_JOURNAL:
			g_journal_flush_done(bp);
			g_journal_flush_send(sc);
			break;
		case GJ_BIO_READ:
		default:
			panic("Invalid bio (%d).", type);
		}
	}
}