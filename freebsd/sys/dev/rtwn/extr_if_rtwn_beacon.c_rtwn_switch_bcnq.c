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
struct rtwn_softc {int cur_bcnq_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtwn_beacon_select (struct rtwn_softc*,int) ; 
 int /*<<< orphan*/  rtwn_check_beacon_valid (struct rtwn_softc*,int) ; 
 int /*<<< orphan*/  rtwn_reset_beacon_valid (struct rtwn_softc*,int) ; 

void
rtwn_switch_bcnq(struct rtwn_softc *sc, int id)
{

	if (sc->cur_bcnq_id != id) {
		/* Wait until any previous transmit completes. */
		(void) rtwn_check_beacon_valid(sc, sc->cur_bcnq_id);

		/* Change current port. */
		rtwn_beacon_select(sc, id);
		sc->cur_bcnq_id = id;
	}

	/* Reset 'beacon valid' bit. */
	rtwn_reset_beacon_valid(sc, id);
}