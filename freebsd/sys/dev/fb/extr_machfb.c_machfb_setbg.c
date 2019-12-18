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
struct machfb_softc {int sc_bg_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_BKGD_CLR ; 
 scalar_t__ MACHFB_CMAP_OFF ; 
 int /*<<< orphan*/  regw (struct machfb_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wait_for_fifo (struct machfb_softc*,int) ; 

__attribute__((used)) static inline void
machfb_setbg(struct machfb_softc *sc, int bg)
{

	if (bg == sc->sc_bg_cache)
		return;
	sc->sc_bg_cache = bg;
	wait_for_fifo(sc, 1);
	regw(sc, DP_BKGD_CLR, bg + MACHFB_CMAP_OFF);
}