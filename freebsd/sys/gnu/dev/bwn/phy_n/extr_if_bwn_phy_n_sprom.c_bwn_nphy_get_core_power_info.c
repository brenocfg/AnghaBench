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
typedef  int uint8_t ;
struct TYPE_2__ {int board_srom_rev; } ;
struct bwn_softc {int /*<<< orphan*/  sc_dev; TYPE_1__ sc_board_info; } ;
struct bwn_phy_n_core_pwr_info {int /*<<< orphan*/  maxpwr_2g; } ;
struct bwn_nphy_power_vars {int /*<<< orphan*/  maxp2ga; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int bhnd_nvram_getvar_uint8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bwn_nphy_get_core_power_info_r11 (struct bwn_softc*,struct bwn_nphy_power_vars const*,struct bwn_phy_n_core_pwr_info*) ; 
 int bwn_nphy_get_core_power_info_r4_r10 (struct bwn_softc*,struct bwn_nphy_power_vars const*,struct bwn_phy_n_core_pwr_info*) ; 
 struct bwn_nphy_power_vars* bwn_nphy_power_vars ; 
 int /*<<< orphan*/  memset (struct bwn_phy_n_core_pwr_info*,int,int) ; 
 int nitems (struct bwn_nphy_power_vars*) ; 

int
bwn_nphy_get_core_power_info(struct bwn_mac *mac, int core,
    struct bwn_phy_n_core_pwr_info *c)
{
	struct bwn_softc			*sc;
	const struct bwn_nphy_power_vars	*v;
	uint8_t					 sromrev;
	int					 error;

	sc = mac->mac_sc;

	if (core < 0 || core >= nitems(bwn_nphy_power_vars))
		return (EINVAL);

	sromrev = sc->sc_board_info.board_srom_rev;
	if (sromrev < 4)
		return (ENXIO);

	v = &bwn_nphy_power_vars[core];

	/* Any power variables not found in NVRAM (or returning a
	 * shorter array for a particular NVRAM revision) should be zero
	 * initialized */
	memset(c, 0x0, sizeof(*c));

	/* Populate SPROM revision-independent values */
	error = bhnd_nvram_getvar_uint8(sc->sc_dev, v->maxp2ga, &c->maxpwr_2g);
	if (error)
		return (error);

	/* Populate SPROM revision-specific values */
	if (sromrev >= 4 && sromrev <= 10)
		return (bwn_nphy_get_core_power_info_r4_r10(sc, v, c));
	else
		return (bwn_nphy_get_core_power_info_r11(sc, v, c));
}