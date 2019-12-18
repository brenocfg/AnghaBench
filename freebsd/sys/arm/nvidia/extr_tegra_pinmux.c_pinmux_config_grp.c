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
struct tegra_grp {int drvdn_mask; int drvdn_shift; int drvup_mask; int drvup_shift; int /*<<< orphan*/  reg; } ;
struct pinmux_softc {int /*<<< orphan*/  pad_mem_res; } ;
struct pincfg {int* params; } ;

/* Variables and functions */
 size_t PROP_ID_DRIVE_DOWN_STRENGTH ; 
 size_t PROP_ID_DRIVE_TYPE ; 
 size_t PROP_ID_DRIVE_UP_STRENGTH ; 
 size_t PROP_ID_HIGH_SPEED_MODE ; 
 size_t PROP_ID_SCHMITT ; 
 size_t PROP_ID_SLEW_RATE_FALLING ; 
 size_t PROP_ID_SLEW_RATE_RISING ; 
 int TEGRA_GRP_DRV_DRVDN_SLWR_MASK ; 
 int TEGRA_GRP_DRV_DRVDN_SLWR_SHIFT ; 
 int TEGRA_GRP_DRV_DRVUP_SLWF_MASK ; 
 int TEGRA_GRP_DRV_DRVUP_SLWF_SHIFT ; 
 int TEGRA_GRP_DRV_TYPE_MASK ; 
 int TEGRA_GRP_DRV_TYPE_SHIFT ; 
 int TEGRA_GRP_HSM_SHIFT ; 
 int TEGRA_GRP_SCHMT_SHIFT ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pinmux_config_grp(struct pinmux_softc *sc, char *grp_name,
    const struct tegra_grp *grp, struct pincfg *cfg)
{
	uint32_t reg;

	reg = bus_read_4(sc->pad_mem_res, grp->reg);

	if (cfg->params[PROP_ID_HIGH_SPEED_MODE] != -1) {
		reg &= ~(1 << TEGRA_GRP_HSM_SHIFT);
		reg |=  (cfg->params[PROP_ID_HIGH_SPEED_MODE] & 1) <<
		    TEGRA_GRP_HSM_SHIFT;
	}
	if (cfg->params[PROP_ID_SCHMITT] != -1) {
		reg &= ~(1 << TEGRA_GRP_SCHMT_SHIFT);
		reg |=  (cfg->params[PROP_ID_SCHMITT] & 1) <<
		    TEGRA_GRP_SCHMT_SHIFT;
	}
	if (cfg->params[PROP_ID_DRIVE_TYPE] != -1) {
		reg &= ~(TEGRA_GRP_DRV_TYPE_MASK << TEGRA_GRP_DRV_TYPE_SHIFT);
		reg |=  (cfg->params[PROP_ID_DRIVE_TYPE] &
		    TEGRA_GRP_DRV_TYPE_MASK) << TEGRA_GRP_DRV_TYPE_SHIFT;
	}
	if (cfg->params[PROP_ID_SLEW_RATE_RISING] != -1) {
		reg &= ~(TEGRA_GRP_DRV_DRVDN_SLWR_MASK <<
		    TEGRA_GRP_DRV_DRVDN_SLWR_SHIFT);
		reg |=  (cfg->params[PROP_ID_SLEW_RATE_RISING] &
		    TEGRA_GRP_DRV_DRVDN_SLWR_MASK) <<
		    TEGRA_GRP_DRV_DRVDN_SLWR_SHIFT;
	}
	if (cfg->params[PROP_ID_SLEW_RATE_FALLING] != -1) {
		reg &= ~(TEGRA_GRP_DRV_DRVUP_SLWF_MASK <<
		    TEGRA_GRP_DRV_DRVUP_SLWF_SHIFT);
		reg |=  (cfg->params[PROP_ID_SLEW_RATE_FALLING] &
		    TEGRA_GRP_DRV_DRVUP_SLWF_MASK) <<
		    TEGRA_GRP_DRV_DRVUP_SLWF_SHIFT;
	}
	if ((cfg->params[PROP_ID_DRIVE_DOWN_STRENGTH] != -1) &&
		 (grp->drvdn_mask != -1)) {
		reg &= ~(grp->drvdn_shift << grp->drvdn_mask);
		reg |=  (cfg->params[PROP_ID_DRIVE_DOWN_STRENGTH] &
		    grp->drvdn_mask) << grp->drvdn_shift;
	}
	if ((cfg->params[PROP_ID_DRIVE_UP_STRENGTH] != -1) &&
		 (grp->drvup_mask != -1)) {
		reg &= ~(grp->drvup_shift << grp->drvup_mask);
		reg |=  (cfg->params[PROP_ID_DRIVE_UP_STRENGTH] &
		    grp->drvup_mask) << grp->drvup_shift;
	}
	bus_write_4(sc->pad_mem_res, grp->reg, reg);
	return (0);
}