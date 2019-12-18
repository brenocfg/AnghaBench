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
struct pfsync_softc {int sc_flags; scalar_t__ sc_bulk_tries; scalar_t__ sc_ureq_sent; int /*<<< orphan*/  sc_bulkfail_tmo; TYPE_1__* sc_ifp; struct pfsync_bucket* sc_buckets; } ;
struct pfsync_bucket {int dummy; } ;
struct TYPE_4__ {scalar_t__ debug; } ;
struct TYPE_3__ {int /*<<< orphan*/  if_vnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int PFSYNCF_OK ; 
 int /*<<< orphan*/  PFSYNC_BLOCK_ASSERT (struct pfsync_softc*) ; 
 int /*<<< orphan*/  PFSYNC_BUCKET_LOCK (struct pfsync_bucket*) ; 
 int /*<<< orphan*/  PFSYNC_BUCKET_UNLOCK (struct pfsync_bucket*) ; 
 int /*<<< orphan*/  PFSYNC_LOCK (struct pfsync_softc*) ; 
 scalar_t__ PFSYNC_MAX_BULKTRIES ; 
 int /*<<< orphan*/  PFSYNC_UNLOCK (struct pfsync_softc*) ; 
 scalar_t__ PF_DEBUG_MISC ; 
 TYPE_2__ V_pf_status ; 
 int /*<<< orphan*/  V_pfsync_carp_adj ; 
 int /*<<< orphan*/  V_pfsyncif ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carp_demote_adj_p (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int /*<<< orphan*/  pfsync_request_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
pfsync_bulk_fail(void *arg)
{
	struct pfsync_softc *sc = arg;
	struct pfsync_bucket *b = &sc->sc_buckets[0];

	CURVNET_SET(sc->sc_ifp->if_vnet);

	PFSYNC_BLOCK_ASSERT(sc);

	if (sc->sc_bulk_tries++ < PFSYNC_MAX_BULKTRIES) {
		/* Try again */
		callout_reset(&sc->sc_bulkfail_tmo, 5 * hz,
		    pfsync_bulk_fail, V_pfsyncif);
		PFSYNC_BUCKET_LOCK(b);
		pfsync_request_update(0, 0);
		PFSYNC_BUCKET_UNLOCK(b);
	} else {
		/* Pretend like the transfer was ok. */
		sc->sc_ureq_sent = 0;
		sc->sc_bulk_tries = 0;
		PFSYNC_LOCK(sc);
		if (!(sc->sc_flags & PFSYNCF_OK) && carp_demote_adj_p)
			(*carp_demote_adj_p)(-V_pfsync_carp_adj,
			    "pfsync bulk fail");
		sc->sc_flags |= PFSYNCF_OK;
		PFSYNC_UNLOCK(sc);
		if (V_pf_status.debug >= PF_DEBUG_MISC)
			printf("pfsync: failed to receive bulk update\n");
	}

	CURVNET_RESTORE();
}