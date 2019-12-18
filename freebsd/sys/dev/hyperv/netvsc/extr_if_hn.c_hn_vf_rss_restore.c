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
struct hn_softc {int hn_flags; int hn_rx_ring_inuse; scalar_t__ hn_rss_hash; scalar_t__ hn_rss_hcap; TYPE_1__* hn_ifp; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_xname; } ;

/* Variables and functions */
 int HN_FLAG_SYNTH_ATTACHED ; 
 int /*<<< orphan*/  HN_LOCK_ASSERT (struct hn_softc*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  NDIS_HASH_ALL ; 
 int /*<<< orphan*/  hn_rss_mbuf_hash (struct hn_softc*,int /*<<< orphan*/ ) ; 
 int hn_rss_reconfig (struct hn_softc*) ; 
 int /*<<< orphan*/  if_printf (TYPE_1__*,char*,int) ; 

__attribute__((used)) static void
hn_vf_rss_restore(struct hn_softc *sc)
{

	HN_LOCK_ASSERT(sc);
	KASSERT(sc->hn_flags & HN_FLAG_SYNTH_ATTACHED,
	    ("%s: synthetic parts are not attached", sc->hn_ifp->if_xname));

	if (sc->hn_rx_ring_inuse == 1)
		goto done;

	/*
	 * Restore hash types.  Key does _not_ matter.
	 */
	if (sc->hn_rss_hash != sc->hn_rss_hcap) {
		int error;

		sc->hn_rss_hash = sc->hn_rss_hcap;
		error = hn_rss_reconfig(sc);
		if (error) {
			if_printf(sc->hn_ifp, "hn_rss_reconfig failed: %d\n",
			    error);
			/* XXX keep going. */
		}
	}
done:
	/* Hash deliverability for mbufs. */
	hn_rss_mbuf_hash(sc, NDIS_HASH_ALL);
}