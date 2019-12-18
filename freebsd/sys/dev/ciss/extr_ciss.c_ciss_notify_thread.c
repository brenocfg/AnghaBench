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
struct ciss_softc {int ciss_flags; int /*<<< orphan*/  ciss_mtx; int /*<<< orphan*/ * ciss_notify_thread; int /*<<< orphan*/  ciss_notify; } ;
struct ciss_request {scalar_t__ cr_data; } ;
struct ciss_notify {int class; } ;

/* Variables and functions */
 int CISS_FLAG_THREAD_SHUT ; 
#define  CISS_NOTIFY_HOTPLUG 130 
#define  CISS_NOTIFY_LOGICAL 129 
#define  CISS_NOTIFY_PHYSICAL 128 
 int /*<<< orphan*/  PUSER ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct ciss_request* ciss_dequeue_notify (struct ciss_softc*) ; 
 int /*<<< orphan*/  ciss_notify_hotplug (struct ciss_softc*,struct ciss_notify*) ; 
 int /*<<< orphan*/  ciss_notify_logical (struct ciss_softc*,struct ciss_notify*) ; 
 int /*<<< orphan*/  ciss_notify_physical (struct ciss_softc*,struct ciss_notify*) ; 
 int /*<<< orphan*/  ciss_release_request (struct ciss_request*) ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
ciss_notify_thread(void *arg)
{
    struct ciss_softc		*sc;
    struct ciss_request		*cr;
    struct ciss_notify		*cn;

    sc = (struct ciss_softc *)arg;
    mtx_lock(&sc->ciss_mtx);

    for (;;) {
	if (STAILQ_EMPTY(&sc->ciss_notify) != 0 &&
	    (sc->ciss_flags & CISS_FLAG_THREAD_SHUT) == 0) {
	    msleep(&sc->ciss_notify, &sc->ciss_mtx, PUSER, "idle", 0);
	}

	if (sc->ciss_flags & CISS_FLAG_THREAD_SHUT)
	    break;

	cr = ciss_dequeue_notify(sc);

	if (cr == NULL)
		panic("cr null");
	cn = (struct ciss_notify *)cr->cr_data;

	switch (cn->class) {
	case CISS_NOTIFY_HOTPLUG:
	    ciss_notify_hotplug(sc, cn);
	    break;
	case CISS_NOTIFY_LOGICAL:
	    ciss_notify_logical(sc, cn);
	    break;
	case CISS_NOTIFY_PHYSICAL:
	    ciss_notify_physical(sc, cn);
	    break;
	}

	ciss_release_request(cr);

    }
    sc->ciss_notify_thread = NULL;
    wakeup(&sc->ciss_notify_thread);

    mtx_unlock(&sc->ciss_mtx);
    kproc_exit(0);
}