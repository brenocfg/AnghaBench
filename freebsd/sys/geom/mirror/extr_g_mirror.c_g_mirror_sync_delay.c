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
struct g_mirror_softc {int /*<<< orphan*/  sc_sync_delayed; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_MIRROR_LOGREQ (int,struct bio*,char*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_queue ; 

__attribute__((used)) static void
g_mirror_sync_delay(struct g_mirror_softc *sc, struct bio *bp)
{

	G_MIRROR_LOGREQ(2, bp, "Delaying synchronization request.");
	TAILQ_INSERT_TAIL(&sc->sc_sync_delayed, bp, bio_queue);
}