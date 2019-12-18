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
typedef  int /*<<< orphan*/  uint32_t ;
struct hn_softc {int hn_rx_ring_cnt; TYPE_1__* hn_rx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  hn_mbuf_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  HN_LOCK_ASSERT (struct hn_softc*) ; 

__attribute__((used)) static void
hn_rss_mbuf_hash(struct hn_softc *sc, uint32_t mbuf_hash)
{
	int i;

	HN_LOCK_ASSERT(sc);

	for (i = 0; i < sc->hn_rx_ring_cnt; ++i)
		sc->hn_rx_ring[i].hn_mbuf_hash = mbuf_hash;
}