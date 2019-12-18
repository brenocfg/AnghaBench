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
typedef  int /*<<< orphan*/  u_char ;
struct gctl_req {int dummy; } ;
struct g_provider {char* name; int /*<<< orphan*/  sectorsize; int /*<<< orphan*/  mediasize; } ;
struct g_geom {struct g_eli_worker* softc; int /*<<< orphan*/  access; int /*<<< orphan*/  dumpconf; int /*<<< orphan*/  resize; void* orphan; void* spoiled; int /*<<< orphan*/  start; } ;
struct g_eli_worker {int sc_nkey; int sc_flags; int sc_cpubind; int w_number; int sc_ealgo; int sc_aalgo; scalar_t__ sc_crypto; int /*<<< orphan*/  sc_queue_mtx; int /*<<< orphan*/  sc_workers; int /*<<< orphan*/  sc_ekeylen; int /*<<< orphan*/  sc_sectorsize; int /*<<< orphan*/  sc_mediasize; int /*<<< orphan*/  w_proc; int /*<<< orphan*/  w_active; struct g_eli_worker* w_softc; int /*<<< orphan*/  sc_ekeys_lock; int /*<<< orphan*/  sc_queue; struct g_geom* sc_geom; } ;
struct g_eli_softc {int sc_nkey; int sc_flags; int sc_cpubind; int w_number; int sc_ealgo; int sc_aalgo; scalar_t__ sc_crypto; int /*<<< orphan*/  sc_queue_mtx; int /*<<< orphan*/  sc_workers; int /*<<< orphan*/  sc_ekeylen; int /*<<< orphan*/  sc_sectorsize; int /*<<< orphan*/  sc_mediasize; int /*<<< orphan*/  w_proc; int /*<<< orphan*/  w_active; struct g_eli_softc* w_softc; int /*<<< orphan*/  sc_ekeys_lock; int /*<<< orphan*/  sc_queue; struct g_geom* sc_geom; } ;
struct g_eli_metadata {int md_flags; } ;
struct g_consumer {int acr; int /*<<< orphan*/ * provider; } ;
struct g_class {int dummy; } ;

/* Variables and functions */
#define  CRYPTO_3DES_CBC 130 
#define  CRYPTO_BLF_CBC 129 
#define  CRYPTO_MD5_HMAC 128 
 scalar_t__ G_ELI_CRYPTO_SW ; 
 int /*<<< orphan*/  G_ELI_DEBUG (int,char*,char*,...) ; 
 int G_ELI_FLAG_AUTH ; 
 int G_ELI_FLAG_DESTROY ; 
 int G_ELI_FLAG_RO ; 
 int G_ELI_FLAG_WO_DETACH ; 
 int /*<<< orphan*/  G_ELI_SUFFIX ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct g_eli_worker*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_ELI ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct g_eli_worker*,int) ; 
 int /*<<< orphan*/  eli_metadata_softc (struct g_eli_worker*,struct g_eli_metadata const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct g_eli_worker*,int /*<<< orphan*/ ) ; 
 int g_access (struct g_consumer*,int,int,int) ; 
 int g_attach (struct g_consumer*,struct g_provider*) ; 
 int /*<<< orphan*/  g_destroy_consumer (struct g_consumer*) ; 
 int /*<<< orphan*/  g_destroy_geom (struct g_geom*) ; 
 int /*<<< orphan*/  g_detach (struct g_consumer*) ; 
 int /*<<< orphan*/  g_eli_access ; 
 char* g_eli_algo2str (int) ; 
 scalar_t__ g_eli_cpu_is_disabled (int) ; 
 int /*<<< orphan*/  g_eli_dumpconf ; 
 int /*<<< orphan*/  g_eli_freesession (struct g_eli_worker*) ; 
 int /*<<< orphan*/  g_eli_key_destroy (struct g_eli_worker*) ; 
 int /*<<< orphan*/  g_eli_mkey_propagate (struct g_eli_worker*,int /*<<< orphan*/  const*) ; 
 int g_eli_newsession (struct g_eli_worker*) ; 
 void* g_eli_orphan ; 
 int /*<<< orphan*/  g_eli_resize ; 
 int /*<<< orphan*/  g_eli_start ; 
 int g_eli_threads ; 
 int /*<<< orphan*/  g_eli_worker ; 
 int /*<<< orphan*/  g_error_provider (struct g_provider*,int /*<<< orphan*/ ) ; 
 struct g_consumer* g_new_consumer (struct g_geom*) ; 
 struct g_geom* g_new_geomf (struct g_class*,char*,char*,int /*<<< orphan*/ ) ; 
 struct g_provider* g_new_providerf (struct g_geom*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_std_access ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,char*,int) ; 
 int /*<<< orphan*/  gone_in (int,char*) ; 
 int kproc_create (int /*<<< orphan*/ ,struct g_eli_worker*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*) ; 
 struct g_eli_worker* malloc (int,int /*<<< orphan*/ ,int) ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w_next ; 
 int /*<<< orphan*/  wakeup (struct g_eli_worker*) ; 

struct g_geom *
g_eli_create(struct gctl_req *req, struct g_class *mp, struct g_provider *bpp,
    const struct g_eli_metadata *md, const u_char *mkey, int nkey)
{
	struct g_eli_softc *sc;
	struct g_eli_worker *wr;
	struct g_geom *gp;
	struct g_provider *pp;
	struct g_consumer *cp;
	u_int i, threads;
	int dcw, error;

	G_ELI_DEBUG(1, "Creating device %s%s.", bpp->name, G_ELI_SUFFIX);

	gp = g_new_geomf(mp, "%s%s", bpp->name, G_ELI_SUFFIX);
	sc = malloc(sizeof(*sc), M_ELI, M_WAITOK | M_ZERO);
	gp->start = g_eli_start;
	/*
	 * Spoiling can happen even though we have the provider open
	 * exclusively, e.g. through media change events.
	 */
	gp->spoiled = g_eli_orphan;
	gp->orphan = g_eli_orphan;
	gp->resize = g_eli_resize;
	gp->dumpconf = g_eli_dumpconf;
	/*
	 * If detach-on-last-close feature is not enabled and we don't operate
	 * on read-only provider, we can simply use g_std_access().
	 */
	if (md->md_flags & (G_ELI_FLAG_WO_DETACH | G_ELI_FLAG_RO))
		gp->access = g_eli_access;
	else
		gp->access = g_std_access;

	eli_metadata_softc(sc, md, bpp->sectorsize, bpp->mediasize);
	sc->sc_nkey = nkey;

	gp->softc = sc;
	sc->sc_geom = gp;

	bioq_init(&sc->sc_queue);
	mtx_init(&sc->sc_queue_mtx, "geli:queue", NULL, MTX_DEF);
	mtx_init(&sc->sc_ekeys_lock, "geli:ekeys", NULL, MTX_DEF);

	pp = NULL;
	cp = g_new_consumer(gp);
	error = g_attach(cp, bpp);
	if (error != 0) {
		if (req != NULL) {
			gctl_error(req, "Cannot attach to %s (error=%d).",
			    bpp->name, error);
		} else {
			G_ELI_DEBUG(1, "Cannot attach to %s (error=%d).",
			    bpp->name, error);
		}
		goto failed;
	}
	/*
	 * Keep provider open all the time, so we can run critical tasks,
	 * like Master Keys deletion, without wondering if we can open
	 * provider or not.
	 * We don't open provider for writing only when user requested read-only
	 * access.
	 */
	dcw = (sc->sc_flags & G_ELI_FLAG_RO) ? 0 : 1;
	error = g_access(cp, 1, dcw, 1);
	if (error != 0) {
		if (req != NULL) {
			gctl_error(req, "Cannot access %s (error=%d).",
			    bpp->name, error);
		} else {
			G_ELI_DEBUG(1, "Cannot access %s (error=%d).",
			    bpp->name, error);
		}
		goto failed;
	}

	/*
	 * Remember the keys in our softc structure.
	 */
	g_eli_mkey_propagate(sc, mkey);

	LIST_INIT(&sc->sc_workers);

	threads = g_eli_threads;
	if (threads == 0)
		threads = mp_ncpus;
	sc->sc_cpubind = (mp_ncpus > 1 && threads == mp_ncpus);
	for (i = 0; i < threads; i++) {
		if (g_eli_cpu_is_disabled(i)) {
			G_ELI_DEBUG(1, "%s: CPU %u disabled, skipping.",
			    bpp->name, i);
			continue;
		}
		wr = malloc(sizeof(*wr), M_ELI, M_WAITOK | M_ZERO);
		wr->w_softc = sc;
		wr->w_number = i;
		wr->w_active = TRUE;

		error = g_eli_newsession(wr);
		if (error != 0) {
			free(wr, M_ELI);
			if (req != NULL) {
				gctl_error(req, "Cannot set up crypto session "
				    "for %s (error=%d).", bpp->name, error);
			} else {
				G_ELI_DEBUG(1, "Cannot set up crypto session "
				    "for %s (error=%d).", bpp->name, error);
			}
			goto failed;
		}

		error = kproc_create(g_eli_worker, wr, &wr->w_proc, 0, 0,
		    "g_eli[%u] %s", i, bpp->name);
		if (error != 0) {
			g_eli_freesession(wr);
			free(wr, M_ELI);
			if (req != NULL) {
				gctl_error(req, "Cannot create kernel thread "
				    "for %s (error=%d).", bpp->name, error);
			} else {
				G_ELI_DEBUG(1, "Cannot create kernel thread "
				    "for %s (error=%d).", bpp->name, error);
			}
			goto failed;
		}
		LIST_INSERT_HEAD(&sc->sc_workers, wr, w_next);
	}

	/*
	 * Create decrypted provider.
	 */
	pp = g_new_providerf(gp, "%s%s", bpp->name, G_ELI_SUFFIX);
	pp->mediasize = sc->sc_mediasize;
	pp->sectorsize = sc->sc_sectorsize;

	g_error_provider(pp, 0);

	G_ELI_DEBUG(0, "Device %s created.", pp->name);
	G_ELI_DEBUG(0, "Encryption: %s %u", g_eli_algo2str(sc->sc_ealgo),
	    sc->sc_ekeylen);
	switch (sc->sc_ealgo) {
	case CRYPTO_3DES_CBC:
		gone_in(13,
		    "support for GEOM_ELI volumes encrypted with 3des");
		break;
	case CRYPTO_BLF_CBC:
		gone_in(13,
		    "support for GEOM_ELI volumes encrypted with blowfish");
		break;
	}
	if (sc->sc_flags & G_ELI_FLAG_AUTH) {
		G_ELI_DEBUG(0, " Integrity: %s", g_eli_algo2str(sc->sc_aalgo));
		switch (sc->sc_aalgo) {
		case CRYPTO_MD5_HMAC:
			gone_in(13,
		    "support for GEOM_ELI volumes authenticated with hmac/md5");
			break;
		}
	}
	G_ELI_DEBUG(0, "    Crypto: %s",
	    sc->sc_crypto == G_ELI_CRYPTO_SW ? "software" : "hardware");
	return (gp);
failed:
	mtx_lock(&sc->sc_queue_mtx);
	sc->sc_flags |= G_ELI_FLAG_DESTROY;
	wakeup(sc);
	/*
	 * Wait for kernel threads self destruction.
	 */
	while (!LIST_EMPTY(&sc->sc_workers)) {
		msleep(&sc->sc_workers, &sc->sc_queue_mtx, PRIBIO,
		    "geli:destroy", 0);
	}
	mtx_destroy(&sc->sc_queue_mtx);
	if (cp->provider != NULL) {
		if (cp->acr == 1)
			g_access(cp, -1, -dcw, -1);
		g_detach(cp);
	}
	g_destroy_consumer(cp);
	g_destroy_geom(gp);
	g_eli_key_destroy(sc);
	bzero(sc, sizeof(*sc));
	free(sc, M_ELI);
	return (NULL);
}