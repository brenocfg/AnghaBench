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
struct ciss_softc {int /*<<< orphan*/  ciss_mtx; int /*<<< orphan*/ * ciss_notify_thread; int /*<<< orphan*/  ciss_notify; int /*<<< orphan*/  ciss_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISS_FLAG_THREAD_SHUT ; 
 int /*<<< orphan*/  PUSER ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ciss_kill_notify_thread(struct ciss_softc *sc)
{

    if (sc->ciss_notify_thread == NULL)
	return;

    sc->ciss_flags |= CISS_FLAG_THREAD_SHUT;
    wakeup(&sc->ciss_notify);
    msleep(&sc->ciss_notify_thread, &sc->ciss_mtx, PUSER, "thtrm", 0);
}