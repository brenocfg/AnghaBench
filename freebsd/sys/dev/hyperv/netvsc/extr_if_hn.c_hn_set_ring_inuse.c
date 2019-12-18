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
struct hn_softc {int hn_rx_ring_cnt; int hn_tx_ring_cnt; int hn_tx_ring_inuse; int hn_rx_ring_inuse; int /*<<< orphan*/  hn_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int rss_getnumbuckets () ; 

__attribute__((used)) static void
hn_set_ring_inuse(struct hn_softc *sc, int ring_cnt)
{
	KASSERT(ring_cnt > 0 && ring_cnt <= sc->hn_rx_ring_cnt,
	    ("invalid ring count %d", ring_cnt));

	if (sc->hn_tx_ring_cnt > ring_cnt)
		sc->hn_tx_ring_inuse = ring_cnt;
	else
		sc->hn_tx_ring_inuse = sc->hn_tx_ring_cnt;
	sc->hn_rx_ring_inuse = ring_cnt;

#ifdef RSS
	if (sc->hn_rx_ring_inuse != rss_getnumbuckets()) {
		if_printf(sc->hn_ifp, "# of RX rings (%d) does not match "
		    "# of RSS buckets (%d)\n", sc->hn_rx_ring_inuse,
		    rss_getnumbuckets());
	}
#endif

	if (bootverbose) {
		if_printf(sc->hn_ifp, "%d TX ring, %d RX ring\n",
		    sc->hn_tx_ring_inuse, sc->hn_rx_ring_inuse);
	}
}