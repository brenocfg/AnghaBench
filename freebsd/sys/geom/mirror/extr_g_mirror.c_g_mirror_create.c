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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_2__ {struct g_geom* ds_geom; scalar_t__ ds_ndisks; } ;
struct g_mirror_softc {int sc_idle; int sc_refcnt; struct g_geom* sc_geom; int /*<<< orphan*/  sc_callout; int /*<<< orphan*/  sc_rootmount; int /*<<< orphan*/  sc_id; int /*<<< orphan*/  sc_ndisks; int /*<<< orphan*/  sc_name; TYPE_1__ sc_sync; int /*<<< orphan*/  sc_worker; scalar_t__ sc_provider_open; int /*<<< orphan*/ * sc_provider; int /*<<< orphan*/  sc_state; int /*<<< orphan*/  sc_done_mtx; int /*<<< orphan*/  sc_events_mtx; int /*<<< orphan*/  sc_events; int /*<<< orphan*/  sc_disks; int /*<<< orphan*/  sc_sync_delayed; int /*<<< orphan*/  sc_inflight; int /*<<< orphan*/  sc_regular_delayed; int /*<<< orphan*/  sc_queue_mtx; int /*<<< orphan*/  sc_queue; int /*<<< orphan*/  sc_lock; scalar_t__ sc_writes; int /*<<< orphan*/  sc_last_write; scalar_t__ sc_bump_id; int /*<<< orphan*/  sc_sectorsize; int /*<<< orphan*/  sc_type; } ;
struct g_mirror_metadata {int md_all; int /*<<< orphan*/  md_name; int /*<<< orphan*/  md_sectorsize; int /*<<< orphan*/  md_mid; } ;
struct g_geom {void* orphan; struct g_mirror_softc* softc; int /*<<< orphan*/  dumpconf; int /*<<< orphan*/  access; int /*<<< orphan*/  start; } ;
struct g_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_MIRROR_DEBUG (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  G_MIRROR_DEVICE_STATE_STARTING ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_MIRROR ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct g_mirror_softc*) ; 
 int /*<<< orphan*/  g_destroy_geom (struct g_geom*) ; 
 int /*<<< orphan*/  g_mirror_access ; 
 int /*<<< orphan*/  g_mirror_dumpconf ; 
 int /*<<< orphan*/  g_mirror_free_device (struct g_mirror_softc*) ; 
 int /*<<< orphan*/  g_mirror_go ; 
 void* g_mirror_orphan ; 
 int /*<<< orphan*/  g_mirror_reinit_from_metadata (struct g_mirror_softc*,struct g_mirror_metadata const*) ; 
 int /*<<< orphan*/  g_mirror_start ; 
 int g_mirror_timeout ; 
 int /*<<< orphan*/  g_mirror_worker ; 
 struct g_geom* g_new_geomf (struct g_class*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int hz ; 
 int kproc_create (int /*<<< orphan*/ ,struct g_mirror_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct g_mirror_softc* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  root_mount_hold (char*) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  time_uptime ; 

struct g_geom *
g_mirror_create(struct g_class *mp, const struct g_mirror_metadata *md,
    u_int type)
{
	struct g_mirror_softc *sc;
	struct g_geom *gp;
	int error, timeout;

	g_topology_assert();
	G_MIRROR_DEBUG(1, "Creating device %s (id=%u).", md->md_name,
	    md->md_mid);

	/* One disk is minimum. */
	if (md->md_all < 1)
		return (NULL);
	/*
	 * Action geom.
	 */
	gp = g_new_geomf(mp, "%s", md->md_name);
	sc = malloc(sizeof(*sc), M_MIRROR, M_WAITOK | M_ZERO);
	gp->start = g_mirror_start;
	gp->orphan = g_mirror_orphan;
	gp->access = g_mirror_access;
	gp->dumpconf = g_mirror_dumpconf;

	sc->sc_type = type;
	sc->sc_id = md->md_mid;
	g_mirror_reinit_from_metadata(sc, md);
	sc->sc_sectorsize = md->md_sectorsize;
	sc->sc_bump_id = 0;
	sc->sc_idle = 1;
	sc->sc_last_write = time_uptime;
	sc->sc_writes = 0;
	sc->sc_refcnt = 1;
	sx_init(&sc->sc_lock, "gmirror:lock");
	TAILQ_INIT(&sc->sc_queue);
	mtx_init(&sc->sc_queue_mtx, "gmirror:queue", NULL, MTX_DEF);
	TAILQ_INIT(&sc->sc_regular_delayed);
	TAILQ_INIT(&sc->sc_inflight);
	TAILQ_INIT(&sc->sc_sync_delayed);
	LIST_INIT(&sc->sc_disks);
	TAILQ_INIT(&sc->sc_events);
	mtx_init(&sc->sc_events_mtx, "gmirror:events", NULL, MTX_DEF);
	callout_init(&sc->sc_callout, 1);
	mtx_init(&sc->sc_done_mtx, "gmirror:done", NULL, MTX_DEF);
	sc->sc_state = G_MIRROR_DEVICE_STATE_STARTING;
	gp->softc = sc;
	sc->sc_geom = gp;
	sc->sc_provider = NULL;
	sc->sc_provider_open = 0;
	/*
	 * Synchronization geom.
	 */
	gp = g_new_geomf(mp, "%s.sync", md->md_name);
	gp->softc = sc;
	gp->orphan = g_mirror_orphan;
	sc->sc_sync.ds_geom = gp;
	sc->sc_sync.ds_ndisks = 0;
	error = kproc_create(g_mirror_worker, sc, &sc->sc_worker, 0, 0,
	    "g_mirror %s", md->md_name);
	if (error != 0) {
		G_MIRROR_DEBUG(1, "Cannot create kernel thread for %s.",
		    sc->sc_name);
		g_destroy_geom(sc->sc_sync.ds_geom);
		g_destroy_geom(sc->sc_geom);
		g_mirror_free_device(sc);
		return (NULL);
	}

	G_MIRROR_DEBUG(1, "Device %s created (%u components, id=%u).",
	    sc->sc_name, sc->sc_ndisks, sc->sc_id);

	sc->sc_rootmount = root_mount_hold("GMIRROR");
	G_MIRROR_DEBUG(1, "root_mount_hold %p", sc->sc_rootmount);
	/*
	 * Run timeout.
	 */
	timeout = g_mirror_timeout * hz;
	callout_reset(&sc->sc_callout, timeout, g_mirror_go, sc);
	return (sc->sc_geom);
}