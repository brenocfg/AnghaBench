#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct md_s {scalar_t__ type; int flags; int fwsectors; int fwheads; char* ident; int (* start ) (struct md_s*,struct bio*) ;int /*<<< orphan*/  devstat; int /*<<< orphan*/  queue_mtx; int /*<<< orphan*/  bio_queue; } ;
struct bio {scalar_t__ bio_cmd; int /*<<< orphan*/  bio_length; int /*<<< orphan*/  bio_completed; int /*<<< orphan*/  bio_bcount; int /*<<< orphan*/  bio_resid; } ;
struct TYPE_5__ {int /*<<< orphan*/  td_pflags; } ;

/* Variables and functions */
 scalar_t__ BIO_GETATTR ; 
 scalar_t__ BIO_READ ; 
 scalar_t__ BIO_WRITE ; 
 int EOPNOTSUPP ; 
 int MD_EXITING ; 
 int MD_SHUTDOWN ; 
 int MD_VERIFY ; 
 scalar_t__ MD_VNODE ; 
 int PDROP ; 
 int PRIBIO ; 
 int /*<<< orphan*/  TDP_NORUNNINGBUF ; 
 struct bio* bioq_takefirst (int /*<<< orphan*/ *) ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  devstat_end_transaction_bio (int /*<<< orphan*/ ,struct bio*) ; 
 scalar_t__ g_handleattr_int (struct bio*,char*,int) ; 
 scalar_t__ g_handleattr_str (struct bio*,char*,char*) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int) ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (struct md_s*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_prio (TYPE_1__*,int) ; 
 int stub1 (struct md_s*,struct bio*) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 

__attribute__((used)) static void
md_kthread(void *arg)
{
	struct md_s *sc;
	struct bio *bp;
	int error;

	sc = arg;
	thread_lock(curthread);
	sched_prio(curthread, PRIBIO);
	thread_unlock(curthread);
	if (sc->type == MD_VNODE)
		curthread->td_pflags |= TDP_NORUNNINGBUF;

	for (;;) {
		mtx_lock(&sc->queue_mtx);
		if (sc->flags & MD_SHUTDOWN) {
			sc->flags |= MD_EXITING;
			mtx_unlock(&sc->queue_mtx);
			kproc_exit(0);
		}
		bp = bioq_takefirst(&sc->bio_queue);
		if (!bp) {
			msleep(sc, &sc->queue_mtx, PRIBIO | PDROP, "mdwait", 0);
			continue;
		}
		mtx_unlock(&sc->queue_mtx);
		if (bp->bio_cmd == BIO_GETATTR) {
			int isv = ((sc->flags & MD_VERIFY) != 0);

			if ((sc->fwsectors && sc->fwheads &&
			    (g_handleattr_int(bp, "GEOM::fwsectors",
			    sc->fwsectors) ||
			    g_handleattr_int(bp, "GEOM::fwheads",
			    sc->fwheads))) ||
			    g_handleattr_int(bp, "GEOM::candelete", 1))
				error = -1;
			else if (sc->ident[0] != '\0' &&
			    g_handleattr_str(bp, "GEOM::ident", sc->ident))
				error = -1;
			else if (g_handleattr_int(bp, "MNT::verified", isv))
				error = -1;
			else
				error = EOPNOTSUPP;
		} else {
			error = sc->start(sc, bp);
		}

		if (bp->bio_cmd == BIO_READ || bp->bio_cmd == BIO_WRITE) {
			/*
			 * Devstat uses (bio_bcount, bio_resid) for
			 * determining the length of the completed part of
			 * the i/o.  g_io_deliver() will translate from
			 * bio_completed to that, but it also destroys the
			 * bio so we must do our own translation.
			 */
			bp->bio_bcount = bp->bio_length;
			bp->bio_resid = (error == -1 ? bp->bio_bcount : 0);
			devstat_end_transaction_bio(sc->devstat, bp);
		}
		if (error != -1) {
			bp->bio_completed = bp->bio_length;
			g_io_deliver(bp, error);
		}
	}
}