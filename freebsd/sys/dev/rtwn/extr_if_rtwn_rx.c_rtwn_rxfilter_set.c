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
struct rtwn_softc {int sc_flags; int /*<<< orphan*/  rcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  R92C_RCR ; 
 int RTWN_RCR_LOCKED ; 
 int /*<<< orphan*/  rtwn_write_4 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
rtwn_rxfilter_set(struct rtwn_softc *sc)
{
	if (!(sc->sc_flags & RTWN_RCR_LOCKED))
		rtwn_write_4(sc, R92C_RCR, sc->rcr);
}