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
struct g_uzip_softc {int wrkthr_flags; int /*<<< orphan*/  (* uzip_do ) (struct g_uzip_softc*,struct bio*) ;int /*<<< orphan*/  queue_mtx; int /*<<< orphan*/  bio_queue; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int GUZ_EXITING ; 
 int GUZ_SHUTDOWN ; 
 int PDROP ; 
 int PRIBIO ; 
 struct bio* bioq_takefirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (struct g_uzip_softc*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_prio (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct g_uzip_softc*,struct bio*) ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 

void
g_uzip_wrkthr(void *arg)
{
	struct g_uzip_softc *sc;
	struct bio *bp;

	sc = (struct g_uzip_softc *)arg;
	thread_lock(curthread);
	sched_prio(curthread, PRIBIO);
	thread_unlock(curthread);

	for (;;) {
		mtx_lock(&sc->queue_mtx);
		if (sc->wrkthr_flags & GUZ_SHUTDOWN) {
			sc->wrkthr_flags |= GUZ_EXITING;
			mtx_unlock(&sc->queue_mtx);
			kproc_exit(0);
		}
		bp = bioq_takefirst(&sc->bio_queue);
		if (!bp) {
			msleep(sc, &sc->queue_mtx, PRIBIO | PDROP,
			    "wrkwait", 0);
			continue;
		}
		mtx_unlock(&sc->queue_mtx);
		sc->uzip_do(sc, bp);
	}
}