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
struct gv_softc {int /*<<< orphan*/  bqueue_mtx; int /*<<< orphan*/  bqueue_down; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bioq_disksort (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct gv_softc*) ; 

__attribute__((used)) static void
gv_post_bio(struct gv_softc *sc, struct bio *bp)
{

	KASSERT(sc != NULL, ("NULL sc"));
	KASSERT(bp != NULL, ("NULL bp"));
	mtx_lock(&sc->bqueue_mtx);
	bioq_disksort(sc->bqueue_down, bp);
	wakeup(sc);
	mtx_unlock(&sc->bqueue_mtx);
}