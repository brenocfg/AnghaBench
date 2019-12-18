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
typedef  struct dtsec_softc* t_Handle ;
struct dtsec_softc {int /*<<< orphan*/  sc_rx_pool; } ;

/* Variables and functions */
 unsigned int DTSEC_RM_POOL_RX_HIGH_MARK ; 
 unsigned int bman_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bman_pool_fill (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
dtsec_rm_pool_rx_depleted(t_Handle h_App, bool in)
{
	struct dtsec_softc *sc;
	unsigned int count;

	sc = h_App;

	if (!in)
		return;

	while (1) {
		count = bman_count(sc->sc_rx_pool);
		if (count > DTSEC_RM_POOL_RX_HIGH_MARK)
			return;

		bman_pool_fill(sc->sc_rx_pool, DTSEC_RM_POOL_RX_HIGH_MARK);
	}
}