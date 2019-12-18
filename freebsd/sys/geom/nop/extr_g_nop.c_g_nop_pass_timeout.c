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
struct g_nop_softc {int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_head_delay; } ;
struct g_nop_delay {TYPE_2__* dl_bio; } ;
struct g_geom {struct g_nop_softc* softc; } ;
struct TYPE_4__ {TYPE_1__* bio_to; } ;
struct TYPE_3__ {struct g_geom* geom; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct g_nop_delay*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dl_next ; 
 int /*<<< orphan*/  g_free (void*) ; 
 int /*<<< orphan*/  g_nop_pass (TYPE_2__*,struct g_geom*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_nop_pass_timeout(void *data)
{
	struct g_nop_softc *sc;
	struct g_geom *gp;
	struct g_nop_delay *gndelay;

	gndelay = (struct g_nop_delay *)data;

	gp = gndelay->dl_bio->bio_to->geom;
	sc = gp->softc;

	mtx_lock(&sc->sc_lock);
	TAILQ_REMOVE(&sc->sc_head_delay, gndelay, dl_next);
	mtx_unlock(&sc->sc_lock);

	g_nop_pass(gndelay->dl_bio, gp);

	g_free(data);
}