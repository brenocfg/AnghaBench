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
struct tegra_mux {int /*<<< orphan*/  reg; } ;
struct pinmux_softc {int /*<<< orphan*/  mux_mem_res; int /*<<< orphan*/  dev; } ;
struct pincfg {int* params; int /*<<< orphan*/ * function; } ;

/* Variables and functions */
 int ENXIO ; 
 size_t PROP_ID_ENABLE_INPUT ; 
 size_t PROP_ID_IORESET ; 
 size_t PROP_ID_LOCK ; 
 size_t PROP_ID_OPEN_DRAIN ; 
 size_t PROP_ID_PULL ; 
 size_t PROP_ID_RCV_SEL ; 
 size_t PROP_ID_TRISTATE ; 
 size_t TEGRA_MUX_ENABLE_INPUT_SHIFT ; 
 int TEGRA_MUX_FUNCTION_MASK ; 
 int TEGRA_MUX_FUNCTION_SHIFT ; 
 int TEGRA_MUX_IORESET_SHIFT ; 
 int TEGRA_MUX_LOCK_SHIFT ; 
 int TEGRA_MUX_PUPD_MASK ; 
 int TEGRA_MUX_PUPD_SHIFT ; 
 int TEGRA_MUX_RCV_SEL_SHIFT ; 
 int TEGRA_MUX_TRISTATE_SHIFT ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*) ; 
 int pinmux_mux_function (struct tegra_mux const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pinmux_config_mux(struct pinmux_softc *sc, char *pin_name,
    const struct tegra_mux *mux, struct pincfg *cfg)
{
	int tmp;
	uint32_t reg;

	reg = bus_read_4(sc->mux_mem_res, mux->reg);

	if (cfg->function != NULL) {
		tmp = pinmux_mux_function(mux, cfg->function);
		if (tmp == -1) {
			device_printf(sc->dev,
			    "Unknown function %s for pin %s\n", cfg->function,
			    pin_name);
			return (ENXIO);
		}
		reg &= ~(TEGRA_MUX_FUNCTION_MASK << TEGRA_MUX_FUNCTION_SHIFT);
		reg |=  (tmp & TEGRA_MUX_FUNCTION_MASK) <<
		    TEGRA_MUX_FUNCTION_SHIFT;
	}
	if (cfg->params[PROP_ID_PULL] != -1) {
		reg &= ~(TEGRA_MUX_PUPD_MASK << TEGRA_MUX_PUPD_SHIFT);
		reg |=  (cfg->params[PROP_ID_PULL] & TEGRA_MUX_PUPD_MASK) <<
		    TEGRA_MUX_PUPD_SHIFT;
	}
	if (cfg->params[PROP_ID_TRISTATE] != -1) {
		reg &= ~(1 << TEGRA_MUX_TRISTATE_SHIFT);
		reg |=  (cfg->params[PROP_ID_TRISTATE] & 1) <<
		    TEGRA_MUX_TRISTATE_SHIFT;
	}
	if (cfg->params[TEGRA_MUX_ENABLE_INPUT_SHIFT] != -1) {
		reg &= ~(1 << TEGRA_MUX_ENABLE_INPUT_SHIFT);
		reg |=  (cfg->params[TEGRA_MUX_ENABLE_INPUT_SHIFT] & 1) <<
		    TEGRA_MUX_ENABLE_INPUT_SHIFT;
	}
	if (cfg->params[PROP_ID_ENABLE_INPUT] != -1) {
		reg &= ~(1 << TEGRA_MUX_ENABLE_INPUT_SHIFT);
		reg |=  (cfg->params[PROP_ID_ENABLE_INPUT] & 1) <<
		    TEGRA_MUX_ENABLE_INPUT_SHIFT;
	}
	if (cfg->params[PROP_ID_ENABLE_INPUT] != -1) {
		reg &= ~(1 << TEGRA_MUX_ENABLE_INPUT_SHIFT);
		reg |=  (cfg->params[PROP_ID_OPEN_DRAIN] & 1) <<
		    TEGRA_MUX_ENABLE_INPUT_SHIFT;
	}
	if (cfg->params[PROP_ID_LOCK] != -1) {
		reg &= ~(1 << TEGRA_MUX_LOCK_SHIFT);
		reg |=  (cfg->params[PROP_ID_LOCK] & 1) <<
		    TEGRA_MUX_LOCK_SHIFT;
	}
	if (cfg->params[PROP_ID_IORESET] != -1) {
		reg &= ~(1 << TEGRA_MUX_IORESET_SHIFT);
		reg |=  (cfg->params[PROP_ID_IORESET] & 1) <<
		    TEGRA_MUX_IORESET_SHIFT;
	}
	if (cfg->params[PROP_ID_RCV_SEL] != -1) {
		reg &= ~(1 << TEGRA_MUX_RCV_SEL_SHIFT);
		reg |=  (cfg->params[PROP_ID_RCV_SEL] & 1) <<
		    TEGRA_MUX_RCV_SEL_SHIFT;
	}
	bus_write_4(sc->mux_mem_res, mux->reg, reg);
	return (0);
}