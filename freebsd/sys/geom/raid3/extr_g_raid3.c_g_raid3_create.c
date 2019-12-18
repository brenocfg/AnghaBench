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
typedef  size_t u_int ;
struct TYPE_4__ {struct g_geom* ds_geom; } ;
struct g_raid3_softc {size_t sc_ndisks; int sc_idle; size_t d_no; struct g_geom* sc_geom; int /*<<< orphan*/  sc_callout; int /*<<< orphan*/  sc_rootmount; int /*<<< orphan*/  sc_id; int /*<<< orphan*/  sc_name; struct g_raid3_softc* sc_disks; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_queue_mtx; int /*<<< orphan*/  sc_events_mtx; TYPE_2__ sc_sync; TYPE_1__* sc_zones; int /*<<< orphan*/  sc_worker; int /*<<< orphan*/ * sc_provider; int /*<<< orphan*/  sc_state; int /*<<< orphan*/  sc_events; int /*<<< orphan*/  sc_sync_delayed; int /*<<< orphan*/  sc_inflight; int /*<<< orphan*/  sc_regular_delayed; int /*<<< orphan*/  sc_queue; int /*<<< orphan*/  d_state; struct g_raid3_softc* d_softc; scalar_t__ sc_writes; int /*<<< orphan*/  sc_last_write; scalar_t__ sc_bump_id; int /*<<< orphan*/  sc_flags; scalar_t__ sc_round_robin; int /*<<< orphan*/  sc_sectorsize; int /*<<< orphan*/  sc_mediasize; } ;
struct g_raid3_metadata {int md_all; int /*<<< orphan*/  md_name; int /*<<< orphan*/  md_mflags; int /*<<< orphan*/  md_sectorsize; int /*<<< orphan*/  md_mediasize; int /*<<< orphan*/  md_id; } ;
struct g_raid3_disk {int dummy; } ;
struct g_geom {void* orphan; struct g_raid3_softc* softc; int /*<<< orphan*/  dumpconf; int /*<<< orphan*/  access; int /*<<< orphan*/  start; } ;
struct g_class {int dummy; } ;
struct TYPE_3__ {void* sz_zone; scalar_t__ sz_failed; scalar_t__ sz_requested; int /*<<< orphan*/  sz_max; scalar_t__ sz_inuse; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID3_DEBUG (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  G_RAID3_DEVICE_STATE_STARTING ; 
 int /*<<< orphan*/  G_RAID3_DISK_STATE_NODISK ; 
 size_t G_RAID3_ZONE_16K ; 
 size_t G_RAID3_ZONE_4K ; 
 size_t G_RAID3_ZONE_64K ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_RAID3 ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct g_raid3_softc*) ; 
 int /*<<< orphan*/  free (struct g_raid3_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_destroy_geom (struct g_geom*) ; 
 struct g_geom* g_new_geomf (struct g_class*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid3_access ; 
 int /*<<< orphan*/  g_raid3_dumpconf ; 
 int /*<<< orphan*/  g_raid3_go ; 
 int /*<<< orphan*/  g_raid3_n16k ; 
 int /*<<< orphan*/  g_raid3_n4k ; 
 int /*<<< orphan*/  g_raid3_n64k ; 
 void* g_raid3_orphan ; 
 int /*<<< orphan*/  g_raid3_start ; 
 int /*<<< orphan*/  g_raid3_timeout ; 
 int /*<<< orphan*/  g_raid3_uma_ctor ; 
 int /*<<< orphan*/  g_raid3_uma_dtor ; 
 int /*<<< orphan*/  g_raid3_use_malloc ; 
 int /*<<< orphan*/  g_raid3_worker ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int hz ; 
 int kproc_create (int /*<<< orphan*/ ,struct g_raid3_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  root_mount_hold (char*) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  time_uptime ; 
 void* uma_zcreate (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zdestroy (void*) ; 

__attribute__((used)) static struct g_geom *
g_raid3_create(struct g_class *mp, const struct g_raid3_metadata *md)
{
	struct g_raid3_softc *sc;
	struct g_geom *gp;
	int error, timeout;
	u_int n;

	g_topology_assert();
	G_RAID3_DEBUG(1, "Creating device %s (id=%u).", md->md_name, md->md_id);

	/* One disk is minimum. */
	if (md->md_all < 1)
		return (NULL);
	/*
	 * Action geom.
	 */
	gp = g_new_geomf(mp, "%s", md->md_name);
	sc = malloc(sizeof(*sc), M_RAID3, M_WAITOK | M_ZERO);
	sc->sc_disks = malloc(sizeof(struct g_raid3_disk) * md->md_all, M_RAID3,
	    M_WAITOK | M_ZERO);
	gp->start = g_raid3_start;
	gp->orphan = g_raid3_orphan;
	gp->access = g_raid3_access;
	gp->dumpconf = g_raid3_dumpconf;

	sc->sc_id = md->md_id;
	sc->sc_mediasize = md->md_mediasize;
	sc->sc_sectorsize = md->md_sectorsize;
	sc->sc_ndisks = md->md_all;
	sc->sc_round_robin = 0;
	sc->sc_flags = md->md_mflags;
	sc->sc_bump_id = 0;
	sc->sc_idle = 1;
	sc->sc_last_write = time_uptime;
	sc->sc_writes = 0;
	for (n = 0; n < sc->sc_ndisks; n++) {
		sc->sc_disks[n].d_softc = sc;
		sc->sc_disks[n].d_no = n;
		sc->sc_disks[n].d_state = G_RAID3_DISK_STATE_NODISK;
	}
	sx_init(&sc->sc_lock, "graid3:lock");
	bioq_init(&sc->sc_queue);
	mtx_init(&sc->sc_queue_mtx, "graid3:queue", NULL, MTX_DEF);
	bioq_init(&sc->sc_regular_delayed);
	bioq_init(&sc->sc_inflight);
	bioq_init(&sc->sc_sync_delayed);
	TAILQ_INIT(&sc->sc_events);
	mtx_init(&sc->sc_events_mtx, "graid3:events", NULL, MTX_DEF);
	callout_init(&sc->sc_callout, 1);
	sc->sc_state = G_RAID3_DEVICE_STATE_STARTING;
	gp->softc = sc;
	sc->sc_geom = gp;
	sc->sc_provider = NULL;
	/*
	 * Synchronization geom.
	 */
	gp = g_new_geomf(mp, "%s.sync", md->md_name);
	gp->softc = sc;
	gp->orphan = g_raid3_orphan;
	sc->sc_sync.ds_geom = gp;

	if (!g_raid3_use_malloc) {
		sc->sc_zones[G_RAID3_ZONE_64K].sz_zone = uma_zcreate("gr3:64k",
		    65536, g_raid3_uma_ctor, g_raid3_uma_dtor, NULL, NULL,
		    UMA_ALIGN_PTR, 0);
		sc->sc_zones[G_RAID3_ZONE_64K].sz_inuse = 0;
		sc->sc_zones[G_RAID3_ZONE_64K].sz_max = g_raid3_n64k;
		sc->sc_zones[G_RAID3_ZONE_64K].sz_requested =
		    sc->sc_zones[G_RAID3_ZONE_64K].sz_failed = 0;
		sc->sc_zones[G_RAID3_ZONE_16K].sz_zone = uma_zcreate("gr3:16k",
		    16384, g_raid3_uma_ctor, g_raid3_uma_dtor, NULL, NULL,
		    UMA_ALIGN_PTR, 0);
		sc->sc_zones[G_RAID3_ZONE_16K].sz_inuse = 0;
		sc->sc_zones[G_RAID3_ZONE_16K].sz_max = g_raid3_n16k;
		sc->sc_zones[G_RAID3_ZONE_16K].sz_requested =
		    sc->sc_zones[G_RAID3_ZONE_16K].sz_failed = 0;
		sc->sc_zones[G_RAID3_ZONE_4K].sz_zone = uma_zcreate("gr3:4k",
		    4096, g_raid3_uma_ctor, g_raid3_uma_dtor, NULL, NULL,
		    UMA_ALIGN_PTR, 0);
		sc->sc_zones[G_RAID3_ZONE_4K].sz_inuse = 0;
		sc->sc_zones[G_RAID3_ZONE_4K].sz_max = g_raid3_n4k;
		sc->sc_zones[G_RAID3_ZONE_4K].sz_requested =
		    sc->sc_zones[G_RAID3_ZONE_4K].sz_failed = 0;
	}

	error = kproc_create(g_raid3_worker, sc, &sc->sc_worker, 0, 0,
	    "g_raid3 %s", md->md_name);
	if (error != 0) {
		G_RAID3_DEBUG(1, "Cannot create kernel thread for %s.",
		    sc->sc_name);
		if (!g_raid3_use_malloc) {
			uma_zdestroy(sc->sc_zones[G_RAID3_ZONE_64K].sz_zone);
			uma_zdestroy(sc->sc_zones[G_RAID3_ZONE_16K].sz_zone);
			uma_zdestroy(sc->sc_zones[G_RAID3_ZONE_4K].sz_zone);
		}
		g_destroy_geom(sc->sc_sync.ds_geom);
		mtx_destroy(&sc->sc_events_mtx);
		mtx_destroy(&sc->sc_queue_mtx);
		sx_destroy(&sc->sc_lock);
		g_destroy_geom(sc->sc_geom);
		free(sc->sc_disks, M_RAID3);
		free(sc, M_RAID3);
		return (NULL);
	}

	G_RAID3_DEBUG(1, "Device %s created (%u components, id=%u).",
	    sc->sc_name, sc->sc_ndisks, sc->sc_id);

	sc->sc_rootmount = root_mount_hold("GRAID3");
	G_RAID3_DEBUG(1, "root_mount_hold %p", sc->sc_rootmount);

	/*
	 * Run timeout.
	 */
	timeout = atomic_load_acq_int(&g_raid3_timeout);
	callout_reset(&sc->sc_callout, timeout * hz, g_raid3_go, sc);
	return (sc->sc_geom);
}