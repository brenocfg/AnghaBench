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
struct g_provider {scalar_t__ mediasize; char* name; int flags; int sectorsize; } ;
struct g_geom {char* name; struct g_gate_softc* softc; int /*<<< orphan*/  dumpconf; int /*<<< orphan*/  orphan; int /*<<< orphan*/  access; int /*<<< orphan*/  start; } ;
struct g_gate_softc {int sc_flags; int sc_seq; scalar_t__ sc_queue_size; int sc_timeout; size_t sc_unit; char* sc_name; scalar_t__ sc_readoffset; int /*<<< orphan*/  sc_queue_mtx; int /*<<< orphan*/  sc_callout; struct g_provider* sc_provider; struct g_consumer* sc_readcons; scalar_t__ sc_queue_count; int /*<<< orphan*/  sc_outqueue; int /*<<< orphan*/  sc_inqueue; int /*<<< orphan*/  sc_info; } ;
struct g_gate_ctl_create {scalar_t__ gctl_mediasize; int gctl_sectorsize; int gctl_flags; size_t gctl_unit; char* gctl_name; scalar_t__ gctl_maxcount; int gctl_timeout; char* gctl_readprov; int gctl_readoffset; int /*<<< orphan*/  gctl_info; } ;
struct g_consumer {int flags; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int G_CF_DIRECT_RECEIVE ; 
 int G_CF_DIRECT_SEND ; 
 int /*<<< orphan*/  G_GATE_DEBUG (int,char*,...) ; 
 int G_GATE_FLAG_READONLY ; 
 int G_GATE_FLAG_WRITEONLY ; 
 scalar_t__ G_GATE_MAX_QUEUE_SIZE ; 
 size_t G_GATE_NAME_GIVEN ; 
 char* G_GATE_PROVIDER_NAME ; 
 size_t G_GATE_UNIT_AUTO ; 
 int G_GATE_USERFLAGS ; 
 int G_PF_DIRECT_RECEIVE ; 
 int G_PF_DIRECT_SEND ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_GATE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int NAME_MAX ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct g_gate_softc*) ; 
 int /*<<< orphan*/  free (struct g_gate_softc*,int /*<<< orphan*/ ) ; 
 int g_access (struct g_consumer*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int g_attach (struct g_consumer*,struct g_provider*) ; 
 int /*<<< orphan*/  g_destroy_consumer (struct g_consumer*) ; 
 int /*<<< orphan*/  g_destroy_geom (struct g_geom*) ; 
 int /*<<< orphan*/  g_detach (struct g_consumer*) ; 
 int /*<<< orphan*/  g_error_provider (struct g_provider*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_gate_access ; 
 int /*<<< orphan*/  g_gate_class ; 
 int /*<<< orphan*/  g_gate_dumpconf ; 
 size_t g_gate_getunit (size_t,int*) ; 
 int /*<<< orphan*/  g_gate_guard ; 
 int g_gate_maxunits ; 
 scalar_t__ g_gate_nunits ; 
 int /*<<< orphan*/  g_gate_orphan ; 
 int /*<<< orphan*/  g_gate_start ; 
 struct g_gate_softc** g_gate_units ; 
 int /*<<< orphan*/  g_gate_units_lock ; 
 struct g_consumer* g_new_consumer (struct g_geom*) ; 
 struct g_geom* g_new_geomf (int /*<<< orphan*/ *,char*,char*) ; 
 struct g_provider* g_new_providerf (struct g_geom*,char*,char*) ; 
 struct g_provider* g_provider_by_name (char*) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int hz ; 
 struct g_gate_softc* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  powerof2 (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
g_gate_create(struct g_gate_ctl_create *ggio)
{
	struct g_gate_softc *sc;
	struct g_geom *gp;
	struct g_provider *pp, *ropp;
	struct g_consumer *cp;
	char name[NAME_MAX];
	int error = 0, unit;

	if (ggio->gctl_mediasize <= 0) {
		G_GATE_DEBUG(1, "Invalid media size.");
		return (EINVAL);
	}
	if (ggio->gctl_sectorsize <= 0) {
		G_GATE_DEBUG(1, "Invalid sector size.");
		return (EINVAL);
	}
	if (!powerof2(ggio->gctl_sectorsize)) {
		G_GATE_DEBUG(1, "Invalid sector size.");
		return (EINVAL);
	}
	if ((ggio->gctl_mediasize % ggio->gctl_sectorsize) != 0) {
		G_GATE_DEBUG(1, "Invalid media size.");
		return (EINVAL);
	}
	if ((ggio->gctl_flags & G_GATE_FLAG_READONLY) != 0 &&
	    (ggio->gctl_flags & G_GATE_FLAG_WRITEONLY) != 0) {
		G_GATE_DEBUG(1, "Invalid flags.");
		return (EINVAL);
	}
	if (ggio->gctl_unit != G_GATE_UNIT_AUTO &&
	    ggio->gctl_unit != G_GATE_NAME_GIVEN &&
	    ggio->gctl_unit < 0) {
		G_GATE_DEBUG(1, "Invalid unit number.");
		return (EINVAL);
	}
	if (ggio->gctl_unit == G_GATE_NAME_GIVEN &&
	    ggio->gctl_name[0] == '\0') {
		G_GATE_DEBUG(1, "No device name.");
		return (EINVAL);
	}

	sc = malloc(sizeof(*sc), M_GATE, M_WAITOK | M_ZERO);
	sc->sc_flags = (ggio->gctl_flags & G_GATE_USERFLAGS);
	strlcpy(sc->sc_info, ggio->gctl_info, sizeof(sc->sc_info));
	sc->sc_seq = 1;
	bioq_init(&sc->sc_inqueue);
	bioq_init(&sc->sc_outqueue);
	mtx_init(&sc->sc_queue_mtx, "gg:queue", NULL, MTX_DEF);
	sc->sc_queue_count = 0;
	sc->sc_queue_size = ggio->gctl_maxcount;
	if (sc->sc_queue_size > G_GATE_MAX_QUEUE_SIZE)
		sc->sc_queue_size = G_GATE_MAX_QUEUE_SIZE;
	sc->sc_timeout = ggio->gctl_timeout;
	callout_init(&sc->sc_callout, 1);

	mtx_lock(&g_gate_units_lock);
	sc->sc_unit = g_gate_getunit(ggio->gctl_unit, &error);
	if (sc->sc_unit < 0)
		goto fail1;
	if (ggio->gctl_unit == G_GATE_NAME_GIVEN)
		snprintf(name, sizeof(name), "%s", ggio->gctl_name);
	else {
		snprintf(name, sizeof(name), "%s%d", G_GATE_PROVIDER_NAME,
		    sc->sc_unit);
	}
	/* Check for name collision. */
	for (unit = 0; unit < g_gate_maxunits; unit++) {
		if (g_gate_units[unit] == NULL)
			continue;
		if (strcmp(name, g_gate_units[unit]->sc_name) != 0)
			continue;
		error = EEXIST;
		goto fail1;
	}
	sc->sc_name = name;
	g_gate_units[sc->sc_unit] = sc;
	g_gate_nunits++;
	mtx_unlock(&g_gate_units_lock);

	g_topology_lock();

	if (ggio->gctl_readprov[0] == '\0') {
		ropp = NULL;
	} else {
		ropp = g_provider_by_name(ggio->gctl_readprov);
		if (ropp == NULL) {
			G_GATE_DEBUG(1, "Provider %s doesn't exist.",
			    ggio->gctl_readprov);
			error = EINVAL;
			goto fail2;
		}
		if ((ggio->gctl_readoffset % ggio->gctl_sectorsize) != 0) {
			G_GATE_DEBUG(1, "Invalid read offset.");
			error = EINVAL;
			goto fail2;
		}
		if (ggio->gctl_mediasize + ggio->gctl_readoffset >
		    ropp->mediasize) {
			G_GATE_DEBUG(1, "Invalid read offset or media size.");
			error = EINVAL;
			goto fail2;
		}
	}

	gp = g_new_geomf(&g_gate_class, "%s", name);
	gp->start = g_gate_start;
	gp->access = g_gate_access;
	gp->orphan = g_gate_orphan;
	gp->dumpconf = g_gate_dumpconf;
	gp->softc = sc;

	if (ropp != NULL) {
		cp = g_new_consumer(gp);
		cp->flags |= G_CF_DIRECT_SEND | G_CF_DIRECT_RECEIVE;
		error = g_attach(cp, ropp);
		if (error != 0) {
			G_GATE_DEBUG(1, "Unable to attach to %s.", ropp->name);
			goto fail3;
		}
		error = g_access(cp, 1, 0, 0);
		if (error != 0) {
			G_GATE_DEBUG(1, "Unable to access %s.", ropp->name);
			g_detach(cp);
			goto fail3;
		}
		sc->sc_readcons = cp;
		sc->sc_readoffset = ggio->gctl_readoffset;
	}

	ggio->gctl_unit = sc->sc_unit;

	pp = g_new_providerf(gp, "%s", name);
	pp->flags |= G_PF_DIRECT_SEND | G_PF_DIRECT_RECEIVE;
	pp->mediasize = ggio->gctl_mediasize;
	pp->sectorsize = ggio->gctl_sectorsize;
	sc->sc_provider = pp;
	g_error_provider(pp, 0);

	g_topology_unlock();
	mtx_lock(&g_gate_units_lock);
	sc->sc_name = sc->sc_provider->name;
	mtx_unlock(&g_gate_units_lock);
	G_GATE_DEBUG(1, "Device %s created.", gp->name);

	if (sc->sc_timeout > 0) {
		callout_reset(&sc->sc_callout, sc->sc_timeout * hz,
		    g_gate_guard, sc);
	}
	return (0);
fail3:
	g_destroy_consumer(cp);
	g_destroy_geom(gp);
fail2:
	g_topology_unlock();
	mtx_lock(&g_gate_units_lock);
	g_gate_units[sc->sc_unit] = NULL;
	KASSERT(g_gate_nunits > 0, ("negative g_gate_nunits?"));
	g_gate_nunits--;
fail1:
	mtx_unlock(&g_gate_units_lock);
	mtx_destroy(&sc->sc_queue_mtx);
	free(sc, M_GATE);
	return (error);
}