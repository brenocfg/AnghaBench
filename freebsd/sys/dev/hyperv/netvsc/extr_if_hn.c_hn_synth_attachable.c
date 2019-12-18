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
struct hn_softc {int hn_flags; int hn_rx_ring_cnt; struct hn_rx_ring* hn_rx_ring; } ;
struct hn_rx_ring {int hn_rx_flags; } ;

/* Variables and functions */
 int HN_FLAG_ERRORS ; 
 int HN_RX_FLAG_BR_REF ; 

__attribute__((used)) static bool
hn_synth_attachable(const struct hn_softc *sc)
{
	int i;

	if (sc->hn_flags & HN_FLAG_ERRORS)
		return (false);

	for (i = 0; i < sc->hn_rx_ring_cnt; ++i) {
		const struct hn_rx_ring *rxr = &sc->hn_rx_ring[i];

		if (rxr->hn_rx_flags & HN_RX_FLAG_BR_REF)
			return (false);
	}
	return (true);
}