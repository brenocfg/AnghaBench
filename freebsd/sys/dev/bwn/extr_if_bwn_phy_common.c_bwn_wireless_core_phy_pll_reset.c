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
typedef  int uint32_t ;
struct bwn_softc {int /*<<< orphan*/ * sc_pmu; int /*<<< orphan*/  sc_dev; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  bhnd_pmu_write_chipctrl (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

int
bwn_wireless_core_phy_pll_reset(struct bwn_mac *mac)
{
	struct bwn_softc	*sc;
	uint32_t		 pll_flag;

	sc = mac->mac_sc;

	if (sc->sc_pmu == NULL) {
		device_printf(sc->sc_dev, "PMU device not found\n");
		return (ENXIO);
	}

	pll_flag = 0x4;
	bhnd_pmu_write_chipctrl(sc->sc_pmu, 0x0, 0x0, pll_flag);
	bhnd_pmu_write_chipctrl(sc->sc_pmu, 0x0, pll_flag, pll_flag);	
	bhnd_pmu_write_chipctrl(sc->sc_pmu, 0x0, 0x0, pll_flag);

	return (0);
}