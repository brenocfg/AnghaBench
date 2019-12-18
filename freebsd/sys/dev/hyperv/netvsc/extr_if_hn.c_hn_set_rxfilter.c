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
typedef  int /*<<< orphan*/  uint32_t ;
struct hn_softc {int /*<<< orphan*/  hn_rx_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  HN_LOCK_ASSERT (struct hn_softc*) ; 
 int hn_rndis_set_rxfilter (struct hn_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hn_set_rxfilter(struct hn_softc *sc, uint32_t filter)
{
	int error = 0;

	HN_LOCK_ASSERT(sc);

	if (sc->hn_rx_filter != filter) {
		error = hn_rndis_set_rxfilter(sc, filter);
		if (!error)
			sc->hn_rx_filter = filter;
	}
	return (error);
}