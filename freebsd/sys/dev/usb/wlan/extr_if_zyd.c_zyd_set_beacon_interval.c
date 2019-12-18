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
typedef  void* uint32_t ;
struct zyd_softc {int sc_atim_wnd; int sc_pre_tbtt; int sc_bcn_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZYD_CR_ATIM_WND_PERIOD ; 
 int /*<<< orphan*/  ZYD_CR_BCN_INTERVAL ; 
 int /*<<< orphan*/  ZYD_CR_PRE_TBTT ; 
 int /*<<< orphan*/  zyd_read32_m (struct zyd_softc*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  zyd_write32_m (struct zyd_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
zyd_set_beacon_interval(struct zyd_softc *sc, int bintval)
{
	int error;
	uint32_t val;

	zyd_read32_m(sc, ZYD_CR_ATIM_WND_PERIOD, &val);
	sc->sc_atim_wnd = val;
	zyd_read32_m(sc, ZYD_CR_PRE_TBTT, &val);
	sc->sc_pre_tbtt = val;
	sc->sc_bcn_int = bintval;

	if (sc->sc_bcn_int <= 5)
		sc->sc_bcn_int = 5;
	if (sc->sc_pre_tbtt < 4 || sc->sc_pre_tbtt >= sc->sc_bcn_int)
		sc->sc_pre_tbtt = sc->sc_bcn_int - 1;
	if (sc->sc_atim_wnd >= sc->sc_pre_tbtt)
		sc->sc_atim_wnd = sc->sc_pre_tbtt - 1;

	zyd_write32_m(sc, ZYD_CR_ATIM_WND_PERIOD, sc->sc_atim_wnd);
	zyd_write32_m(sc, ZYD_CR_PRE_TBTT, sc->sc_pre_tbtt);
	zyd_write32_m(sc, ZYD_CR_BCN_INTERVAL, sc->sc_bcn_int);
fail:
	return (error);
}