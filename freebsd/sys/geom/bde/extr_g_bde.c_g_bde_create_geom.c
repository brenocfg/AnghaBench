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
struct gctl_req {int dummy; } ;
struct g_provider {int stripesize; int sectorsize; int /*<<< orphan*/  mediasize; scalar_t__ stripeoffset; int /*<<< orphan*/  name; } ;
struct g_geom {struct g_bde_softc* softc; int /*<<< orphan*/  name; } ;
struct g_consumer {TYPE_1__* provider; } ;
struct g_class {int /*<<< orphan*/  name; } ;
struct g_bde_key {int keys_per_sector; int sectorsize; int zone_cont; int zone_width; scalar_t__ sector0; scalar_t__ sectorN; scalar_t__ media_width; } ;
struct g_bde_softc {void* sha2; int zone_cont; int sectorsize; int /*<<< orphan*/  mediasize; int /*<<< orphan*/  thread; int /*<<< orphan*/  worklist_mutex; int /*<<< orphan*/  worklist; int /*<<< orphan*/  freelist; struct g_bde_key key; struct g_consumer* consumer; struct g_geom* geom; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int /*<<< orphan*/  mediasize; int /*<<< orphan*/  sectorsize; } ;

/* Variables and functions */
#define  EINVAL 131 
#define  ENOENT 130 
#define  ENOTDIR 129 
#define  ESRCH 128 
 int G_BDE_MAXKEYS ; 
 int G_BDE_SKEYLEN ; 
 int /*<<< orphan*/  G_T_TOPOLOGY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int SHA512_DIGEST_LENGTH ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 int g_access (struct g_consumer*,int,int,int) ; 
 int /*<<< orphan*/  g_attach (struct g_consumer*,struct g_provider*) ; 
 int g_bde_decrypt_lock (struct g_bde_softc*,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_bde_max_sector (struct g_bde_key*) ; 
 int /*<<< orphan*/  g_bde_worker ; 
 int /*<<< orphan*/  g_destroy_consumer (struct g_consumer*) ; 
 int /*<<< orphan*/  g_destroy_geom (struct g_geom*) ; 
 int /*<<< orphan*/  g_detach (struct g_consumer*) ; 
 int /*<<< orphan*/  g_error_provider (struct g_provider*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (struct g_bde_softc*) ; 
 struct g_bde_softc* g_malloc (int,int) ; 
 struct g_consumer* g_new_consumer (struct g_geom*) ; 
 struct g_geom* g_new_geomf (struct g_class*,char*,int /*<<< orphan*/ ) ; 
 struct g_provider* g_new_providerf (struct g_geom*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_trace (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 void* gctl_get_param (struct gctl_req*,char*,int*) ; 
 int /*<<< orphan*/  kproc_create (int /*<<< orphan*/ ,struct g_geom*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_bde_create_geom(struct gctl_req *req, struct g_class *mp, struct g_provider *pp)
{
	struct g_geom *gp;
	struct g_consumer *cp;
	struct g_bde_key *kp;
	int error, i;
	u_int sectorsize;
	off_t mediasize;
	struct g_bde_softc *sc;
	void *pass;
	void *key;

	g_trace(G_T_TOPOLOGY, "g_bde_create_geom(%s, %s)", mp->name, pp->name);
	g_topology_assert();
	gp = NULL;


	gp = g_new_geomf(mp, "%s.bde", pp->name);
	cp = g_new_consumer(gp);
	g_attach(cp, pp);
	error = g_access(cp, 1, 1, 1);
	if (error) {
		g_detach(cp);
		g_destroy_consumer(cp);
		g_destroy_geom(gp);
		gctl_error(req, "could not access consumer");
		return;
	}
	pass = NULL;
	key = NULL;
	do {
		pass = gctl_get_param(req, "pass", &i);
		if (pass == NULL || i != SHA512_DIGEST_LENGTH) {
			gctl_error(req, "No usable key presented");
			break;
		}
		key = gctl_get_param(req, "key", &i);
		if (key != NULL && i != 16) {
			gctl_error(req, "Invalid key presented");
			break;
		}
		sectorsize = cp->provider->sectorsize;
		mediasize = cp->provider->mediasize;
		sc = g_malloc(sizeof(struct g_bde_softc), M_WAITOK | M_ZERO);
		gp->softc = sc;
		sc->geom = gp;
		sc->consumer = cp;

		error = g_bde_decrypt_lock(sc, pass, key,
		    mediasize, sectorsize, NULL);
		bzero(sc->sha2, sizeof sc->sha2);
		if (error)
			break;
		kp = &sc->key;

		/* Initialize helper-fields */
		kp->keys_per_sector = kp->sectorsize / G_BDE_SKEYLEN;
		kp->zone_cont = kp->keys_per_sector * kp->sectorsize;
		kp->zone_width = kp->zone_cont + kp->sectorsize;
		kp->media_width = kp->sectorN - kp->sector0 -
		    G_BDE_MAXKEYS * kp->sectorsize;

		/* Our external parameters */
		sc->zone_cont = kp->zone_cont;
		sc->mediasize = g_bde_max_sector(kp);
		sc->sectorsize = kp->sectorsize;

		TAILQ_INIT(&sc->freelist);
		TAILQ_INIT(&sc->worklist);
		mtx_init(&sc->worklist_mutex, "g_bde_worklist", NULL, MTX_DEF);
		/* XXX: error check */
		kproc_create(g_bde_worker, gp, &sc->thread, 0, 0,
			"g_bde %s", gp->name);
		pp = g_new_providerf(gp, "%s", gp->name);
		pp->stripesize = kp->zone_cont;
		pp->stripeoffset = 0;
		pp->mediasize = sc->mediasize;
		pp->sectorsize = sc->sectorsize;
		g_error_provider(pp, 0);
		break;
	} while (0);
	if (pass != NULL)
		bzero(pass, SHA512_DIGEST_LENGTH);
	if (key != NULL)
		bzero(key, 16);
	if (error == 0)
		return;
	g_access(cp, -1, -1, -1);
	g_detach(cp);
	g_destroy_consumer(cp);
	if (gp->softc != NULL)
		g_free(gp->softc);
	g_destroy_geom(gp);
	switch (error) {
	case ENOENT:
		gctl_error(req, "Lock was destroyed");
		break;
	case ESRCH:
		gctl_error(req, "Lock was nuked");
		break;
	case EINVAL:
		gctl_error(req, "Could not open lock");
		break;
	case ENOTDIR:
		gctl_error(req, "Lock not found");
		break;
	default:
		gctl_error(req, "Could not open lock (%d)", error);
		break;
	}
	return;
}