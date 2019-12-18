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
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTWN_ASSERT_LOCKED (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_rxfilter_update_mgt (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_set_promisc (struct rtwn_softc*) ; 

void
rtwn_rxfilter_update(struct rtwn_softc *sc)
{

	RTWN_ASSERT_LOCKED(sc);

	/* Filter for management frames. */
	rtwn_rxfilter_update_mgt(sc);

	/* Update Rx filter. */
	rtwn_set_promisc(sc);
}