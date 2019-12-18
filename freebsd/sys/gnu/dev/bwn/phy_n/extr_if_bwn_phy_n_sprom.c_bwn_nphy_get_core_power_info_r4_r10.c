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
struct bwn_softc {int /*<<< orphan*/  sc_dev; } ;
struct bwn_phy_n_core_pwr_info {int /*<<< orphan*/  itssi_5g; int /*<<< orphan*/  itssi_2g; } ;
struct bwn_nphy_power_vars {int /*<<< orphan*/  itt5ga; int /*<<< orphan*/  itt2ga; } ;

/* Variables and functions */
 int bhnd_nvram_getvar_uint8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bwn_nphy_get_core_power_info_r4_r10(struct bwn_softc *sc,
    const struct bwn_nphy_power_vars *v, struct bwn_phy_n_core_pwr_info *c)
{
	int error;

	/* BHND_NVAR_ITT2GA[core] */
	error = bhnd_nvram_getvar_uint8(sc->sc_dev, v->itt2ga, &c->itssi_2g);
	if (error)
		return (error);

	/* BHND_NVAR_ITT5GA[core] */
	error = bhnd_nvram_getvar_uint8(sc->sc_dev, v->itt5ga, &c->itssi_5g);
	if (error)
		return (error);

	return (0);
}