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
struct g_cache_softc {int sc_maxent; int sc_nused; int /*<<< orphan*/  sc_usedlist; int /*<<< orphan*/  sc_mtx; } ;
struct g_cache_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct g_cache_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct g_cache_desc* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct g_cache_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_next ; 
 int /*<<< orphan*/  d_used ; 
 int /*<<< orphan*/  g_cache_free (struct g_cache_softc*,struct g_cache_desc*) ; 
 int g_cache_used_lo ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_cache_free_used(struct g_cache_softc *sc)
{
	struct g_cache_desc *dp;
	u_int n;

	mtx_assert(&sc->sc_mtx, MA_OWNED);

	n = g_cache_used_lo * sc->sc_maxent / 100;
	while (sc->sc_nused > n) {
		KASSERT(!TAILQ_EMPTY(&sc->sc_usedlist), ("used list empty"));
		dp = TAILQ_FIRST(&sc->sc_usedlist);
		TAILQ_REMOVE(&sc->sc_usedlist, dp, d_used);
		sc->sc_nused--;
		LIST_REMOVE(dp, d_next);
		g_cache_free(sc, dp);
	}
}