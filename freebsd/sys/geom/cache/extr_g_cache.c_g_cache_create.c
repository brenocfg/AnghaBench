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
typedef  int u_int ;
struct g_provider {int sectorsize; int mediasize; int /*<<< orphan*/  name; } ;
struct g_geom {int /*<<< orphan*/  name; int /*<<< orphan*/  dumpconf; int /*<<< orphan*/  access; int /*<<< orphan*/  orphan; int /*<<< orphan*/  start; struct g_cache_softc* softc; } ;
struct g_consumer {int dummy; } ;
struct g_class {int dummy; } ;
struct g_cache_softc {int sc_type; int sc_bshift; int sc_bsize; int sc_maxent; int /*<<< orphan*/  sc_callout; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_tail; struct g_geom* sc_geom; int /*<<< orphan*/  sc_usedlist; int /*<<< orphan*/ * sc_desclist; int /*<<< orphan*/  sc_zone; } ;
struct g_cache_metadata {int md_size; int md_bsize; int /*<<< orphan*/  md_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNO2OFF (int /*<<< orphan*/ ,struct g_cache_softc*) ; 
 int G_CACHE_BUCKETS ; 
 int /*<<< orphan*/  G_CACHE_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int G_CACHE_TYPE_AUTOMATIC ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int MAXPHYS ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OFF2BNO (int,struct g_cache_softc*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct g_cache_softc*) ; 
 int ffs (int) ; 
 scalar_t__ g_attach (struct g_consumer*,struct g_provider*) ; 
 int /*<<< orphan*/  g_cache_access ; 
 int /*<<< orphan*/  g_cache_dumpconf ; 
 int /*<<< orphan*/ * g_cache_find_device (struct g_class*,char const*) ; 
 int /*<<< orphan*/  g_cache_go ; 
 int /*<<< orphan*/  g_cache_orphan ; 
 int /*<<< orphan*/  g_cache_start ; 
 int g_cache_timeout ; 
 int /*<<< orphan*/  g_destroy_consumer (struct g_consumer*) ; 
 int /*<<< orphan*/  g_destroy_geom (struct g_geom*) ; 
 int /*<<< orphan*/  g_destroy_provider (struct g_provider*) ; 
 int /*<<< orphan*/  g_error_provider (struct g_provider*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (struct g_cache_softc*) ; 
 struct g_cache_softc* g_malloc (int,int) ; 
 struct g_consumer* g_new_consumer (struct g_geom*) ; 
 struct g_geom* g_new_geomf (struct g_class*,char*,int /*<<< orphan*/ ) ; 
 struct g_provider* g_new_providerf (struct g_geom*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int hz ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct g_geom *
g_cache_create(struct g_class *mp, struct g_provider *pp,
    const struct g_cache_metadata *md, u_int type)
{
	struct g_cache_softc *sc;
	struct g_geom *gp;
	struct g_provider *newpp;
	struct g_consumer *cp;
	u_int bshift;
	int i;

	g_topology_assert();

	gp = NULL;
	newpp = NULL;
	cp = NULL;

	G_CACHE_DEBUG(1, "Creating device %s.", md->md_name);

	/* Cache size is minimum 100. */
	if (md->md_size < 100) {
		G_CACHE_DEBUG(0, "Invalid size for device %s.", md->md_name);
		return (NULL);
	}

	/* Block size restrictions. */
	bshift = ffs(md->md_bsize) - 1;
	if (md->md_bsize == 0 || md->md_bsize > MAXPHYS ||
	    md->md_bsize != 1 << bshift ||
	    (md->md_bsize % pp->sectorsize) != 0) {
		G_CACHE_DEBUG(0, "Invalid blocksize for provider %s.", pp->name);
		return (NULL);
	}

	/* Check for duplicate unit. */
	if (g_cache_find_device(mp, (const char *)&md->md_name) != NULL) {
		G_CACHE_DEBUG(0, "Provider %s already exists.", md->md_name);
		return (NULL);
	}

	gp = g_new_geomf(mp, "%s", md->md_name);
	sc = g_malloc(sizeof(*sc), M_WAITOK | M_ZERO);
	sc->sc_type = type;
	sc->sc_bshift = bshift;
	sc->sc_bsize = 1 << bshift;
	sc->sc_zone = uma_zcreate("gcache", sc->sc_bsize, NULL, NULL, NULL, NULL,
	    UMA_ALIGN_PTR, 0);
	mtx_init(&sc->sc_mtx, "GEOM CACHE mutex", NULL, MTX_DEF);
	for (i = 0; i < G_CACHE_BUCKETS; i++)
		LIST_INIT(&sc->sc_desclist[i]);
	TAILQ_INIT(&sc->sc_usedlist);
	sc->sc_maxent = md->md_size;
	callout_init_mtx(&sc->sc_callout, &sc->sc_mtx, 0);
	gp->softc = sc;
	sc->sc_geom = gp;
	gp->start = g_cache_start;
	gp->orphan = g_cache_orphan;
	gp->access = g_cache_access;
	gp->dumpconf = g_cache_dumpconf;

	newpp = g_new_providerf(gp, "cache/%s", gp->name);
	newpp->sectorsize = pp->sectorsize;
	newpp->mediasize = pp->mediasize;
	if (type == G_CACHE_TYPE_AUTOMATIC)
		newpp->mediasize -= pp->sectorsize;
	sc->sc_tail = BNO2OFF(OFF2BNO(newpp->mediasize, sc), sc);

	cp = g_new_consumer(gp);
	if (g_attach(cp, pp) != 0) {
		G_CACHE_DEBUG(0, "Cannot attach to provider %s.", pp->name);
		g_destroy_consumer(cp);
		g_destroy_provider(newpp);
		mtx_destroy(&sc->sc_mtx);
		g_free(sc);
		g_destroy_geom(gp);
		return (NULL);
	}

	g_error_provider(newpp, 0);
	G_CACHE_DEBUG(0, "Device %s created.", gp->name);
	callout_reset(&sc->sc_callout, g_cache_timeout * hz, g_cache_go, sc);
	return (gp);
}