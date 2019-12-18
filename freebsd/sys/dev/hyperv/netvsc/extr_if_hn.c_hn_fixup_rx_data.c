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
struct hn_softc {int hn_caps; int hn_rx_ring_cnt; TYPE_1__* hn_rx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  hn_rx_flags; } ;

/* Variables and functions */
 int HN_CAP_UDPHASH ; 
 int /*<<< orphan*/  HN_RX_FLAG_UDP_HASH ; 

__attribute__((used)) static void
hn_fixup_rx_data(struct hn_softc *sc)
{

	if (sc->hn_caps & HN_CAP_UDPHASH) {
		int i;

		for (i = 0; i < sc->hn_rx_ring_cnt; ++i)
			sc->hn_rx_ring[i].hn_rx_flags |= HN_RX_FLAG_UDP_HASH;
	}
}