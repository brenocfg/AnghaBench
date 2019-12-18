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
struct arswitch_softc {int /*<<< orphan*/  sc_dev; } ;
struct ar8327_sgmii_cfg {int sgmii_ctrl; int serdes_aen; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int
ar8327_fetch_pdata_sgmii(struct arswitch_softc *sc,
    struct ar8327_sgmii_cfg *scfg)
{
	int val;

	/* sgmii_ctrl */
	val = 0;
	if (resource_int_value(device_get_name(sc->sc_dev),
	    device_get_unit(sc->sc_dev),
	    "sgmii.ctrl", &val) != 0)
		return (0);
	scfg->sgmii_ctrl = val;

	/* serdes_aen */
	val = 0;
	if (resource_int_value(device_get_name(sc->sc_dev),
	    device_get_unit(sc->sc_dev),
	    "sgmii.serdes_aen", &val) != 0)
		return (0);
	scfg->serdes_aen = val;

	return (1);
}