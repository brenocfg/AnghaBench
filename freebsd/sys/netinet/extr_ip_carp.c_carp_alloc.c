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
struct ifnet {struct carp_if* if_carp; } ;
struct ifaddr {int dummy; } ;
struct carp_softc {int sc_vhid; int sc_init_counter; int sc_ifasiz; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_ad_tmo; int /*<<< orphan*/  sc_md6_tmo; int /*<<< orphan*/  sc_md_tmo; struct ifnet* sc_carpdev; void* sc_ifas; int /*<<< orphan*/  sc_state; int /*<<< orphan*/  sc_advbase; } ;
struct carp_if {int /*<<< orphan*/  cif_vrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLOUT_RETURNUNLOCKED ; 
 int /*<<< orphan*/  CARP_DFLTINTV ; 
 int /*<<< orphan*/  CARP_LOCK_INIT (struct carp_softc*) ; 
 int /*<<< orphan*/  CIF_LOCK (struct carp_if*) ; 
 int /*<<< orphan*/  CIF_UNLOCK (struct carp_if*) ; 
 int /*<<< orphan*/  INIT ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct carp_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_CARP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct carp_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct carp_if* carp_alloc_if (struct ifnet*) ; 
 int /*<<< orphan*/  carp_list ; 
 int /*<<< orphan*/  carp_mtx ; 
 int /*<<< orphan*/  carp_sx ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sc_list ; 
 int /*<<< orphan*/  sc_next ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct carp_softc*
carp_alloc(struct ifnet *ifp)
{
	struct carp_softc *sc;
	struct carp_if *cif;

	sx_assert(&carp_sx, SA_XLOCKED);

	if ((cif = ifp->if_carp) == NULL)
		cif = carp_alloc_if(ifp);

	sc = malloc(sizeof(*sc), M_CARP, M_WAITOK|M_ZERO);

	sc->sc_advbase = CARP_DFLTINTV;
	sc->sc_vhid = -1;	/* required setting */
	sc->sc_init_counter = 1;
	sc->sc_state = INIT;

	sc->sc_ifasiz = sizeof(struct ifaddr *);
	sc->sc_ifas = malloc(sc->sc_ifasiz, M_CARP, M_WAITOK|M_ZERO);
	sc->sc_carpdev = ifp;

	CARP_LOCK_INIT(sc);
#ifdef INET
	callout_init_mtx(&sc->sc_md_tmo, &sc->sc_mtx, CALLOUT_RETURNUNLOCKED);
#endif
#ifdef INET6
	callout_init_mtx(&sc->sc_md6_tmo, &sc->sc_mtx, CALLOUT_RETURNUNLOCKED);
#endif
	callout_init_mtx(&sc->sc_ad_tmo, &sc->sc_mtx, CALLOUT_RETURNUNLOCKED);

	CIF_LOCK(cif);
	TAILQ_INSERT_TAIL(&cif->cif_vrs, sc, sc_list);
	CIF_UNLOCK(cif);

	mtx_lock(&carp_mtx);
	LIST_INSERT_HEAD(&carp_list, sc, sc_next);
	mtx_unlock(&carp_mtx);

	return (sc);
}