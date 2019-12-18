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
struct g_cache_softc {int /*<<< orphan*/  sc_nent; int /*<<< orphan*/  sc_zone; int /*<<< orphan*/  sc_mtx; } ;
struct g_cache_desc {int /*<<< orphan*/  d_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_GCACHE ; 
 int /*<<< orphan*/  free (struct g_cache_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_cache_free(struct g_cache_softc *sc, struct g_cache_desc *dp)
{

	mtx_assert(&sc->sc_mtx, MA_OWNED);

	uma_zfree(sc->sc_zone, dp->d_data);
	free(dp, M_GCACHE);
	sc->sc_nent--;
}