#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct g_virstor_softc {size_t n_components; struct g_virstor_softc* components; struct g_virstor_softc* map; int /*<<< orphan*/  delayed_bio_q_mtx; int /*<<< orphan*/  delayed_bio_q; TYPE_1__* bio; struct g_provider* provider; struct g_geom* geom; int /*<<< orphan*/ * gcons; } ;
struct g_virstor_bio_q {size_t n_components; struct g_virstor_bio_q* components; struct g_virstor_bio_q* map; int /*<<< orphan*/  delayed_bio_q_mtx; int /*<<< orphan*/  delayed_bio_q; TYPE_1__* bio; struct g_provider* provider; struct g_geom* geom; int /*<<< orphan*/ * gcons; } ;
struct g_provider {scalar_t__ acr; scalar_t__ acw; scalar_t__ ace; int /*<<< orphan*/  name; } ;
struct g_geom {int /*<<< orphan*/  name; int /*<<< orphan*/  provider; int /*<<< orphan*/ * softc; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  bio_error; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOSPC ; 
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct g_provider* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_MSG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LVL_DEBUG ; 
 int /*<<< orphan*/  LVL_ERROR ; 
 int /*<<< orphan*/  LVL_WARNING ; 
 int /*<<< orphan*/  M_GVIRSTOR ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct g_virstor_softc* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct g_virstor_softc*,int) ; 
 int /*<<< orphan*/  free (struct g_virstor_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_io_deliver (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_wither_geom (struct g_geom*,int) ; 
 int /*<<< orphan*/  linkage ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_component (struct g_virstor_softc*,struct g_virstor_softc*,scalar_t__) ; 

__attribute__((used)) static int
virstor_geom_destroy(struct g_virstor_softc *sc, boolean_t force,
    boolean_t delay)
{
	struct g_provider *pp;
	struct g_geom *gp;
	u_int n;

	g_topology_assert();

	if (sc == NULL)
		return (ENXIO);

	pp = sc->provider;
	if (pp != NULL && (pp->acr != 0 || pp->acw != 0 || pp->ace != 0)) {
		LOG_MSG(force ? LVL_WARNING : LVL_ERROR,
		    "Device %s is still open.", pp->name);
		if (!force)
			return (EBUSY);
	}

	for (n = 0; n < sc->n_components; n++) {
		if (sc->components[n].gcons != NULL)
			remove_component(sc, &sc->components[n], delay);
	}

	gp = sc->geom;
	gp->softc = NULL;

	KASSERT(sc->provider == NULL, ("Provider still exists for %s",
	    gp->name));

	/* XXX: This might or might not work, since we're called with
	 * the topology lock held. Also, it might panic the kernel if
	 * the error'd BIO is in softupdates code. */
	mtx_lock(&sc->delayed_bio_q_mtx);
	while (!STAILQ_EMPTY(&sc->delayed_bio_q)) {
		struct g_virstor_bio_q *bq;
		bq = STAILQ_FIRST(&sc->delayed_bio_q);
		bq->bio->bio_error = ENOSPC;
		g_io_deliver(bq->bio, EIO);
		STAILQ_REMOVE_HEAD(&sc->delayed_bio_q, linkage);
		free(bq, M_GVIRSTOR);
	}
	mtx_unlock(&sc->delayed_bio_q_mtx);
	mtx_destroy(&sc->delayed_bio_q_mtx);

	free(sc->map, M_GVIRSTOR);
	free(sc->components, M_GVIRSTOR);
	bzero(sc, sizeof *sc);
	free(sc, M_GVIRSTOR);

	pp = LIST_FIRST(&gp->provider); /* We only offer one provider */
	if (pp == NULL || (pp->acr == 0 && pp->acw == 0 && pp->ace == 0))
		LOG_MSG(LVL_DEBUG, "Device %s destroyed", gp->name);

	g_wither_geom(gp, ENXIO);

	return (0);
}