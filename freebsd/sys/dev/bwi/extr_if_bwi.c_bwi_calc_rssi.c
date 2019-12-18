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
struct bwi_softc {TYPE_1__* sc_cur_regwin; } ;
struct bwi_rxbuf_hdr {int dummy; } ;
struct bwi_mac {int dummy; } ;
struct TYPE_2__ {scalar_t__ rw_type; } ;

/* Variables and functions */
 scalar_t__ BWI_REGWIN_T_MAC ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int bwi_rf_calc_rssi (struct bwi_mac*,struct bwi_rxbuf_hdr const*) ; 

__attribute__((used)) static int
bwi_calc_rssi(struct bwi_softc *sc, const struct bwi_rxbuf_hdr *hdr)
{
	struct bwi_mac *mac;

	KASSERT(sc->sc_cur_regwin->rw_type == BWI_REGWIN_T_MAC,
	    ("current regwin type %d", sc->sc_cur_regwin->rw_type));
	mac = (struct bwi_mac *)sc->sc_cur_regwin;

	return bwi_rf_calc_rssi(mac, hdr);
}