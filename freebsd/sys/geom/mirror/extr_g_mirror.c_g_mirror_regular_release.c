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
struct g_mirror_softc {int /*<<< orphan*/  sc_queue_mtx; int /*<<< orphan*/  sc_queue; int /*<<< orphan*/  sc_regular_delayed; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_MIRROR_DEBUG (int,char*) ; 
 int /*<<< orphan*/  TAILQ_CONCAT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct bio* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_SWAP (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio ; 
 int /*<<< orphan*/  bio_queue ; 
 scalar_t__ g_mirror_sync_collision (struct g_mirror_softc*,struct bio*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_mirror_regular_release(struct g_mirror_softc *sc)
{
	struct bio *bp;

	if ((bp = TAILQ_FIRST(&sc->sc_regular_delayed)) == NULL)
		return;
	if (g_mirror_sync_collision(sc, bp))
		return;

	G_MIRROR_DEBUG(2, "Requeuing regular requests after collision.");
	mtx_lock(&sc->sc_queue_mtx);
	TAILQ_CONCAT(&sc->sc_regular_delayed, &sc->sc_queue, bio_queue);
	TAILQ_SWAP(&sc->sc_regular_delayed, &sc->sc_queue, bio, bio_queue);
	mtx_unlock(&sc->sc_queue_mtx);
}