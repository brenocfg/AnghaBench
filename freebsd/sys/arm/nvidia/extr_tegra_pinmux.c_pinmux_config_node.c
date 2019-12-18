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
struct tegra_mux {int gpio_num; } ;
struct tegra_grp {int dummy; } ;
struct pinmux_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  mipi_mem_res; } ;
struct pincfg {char* function; } ;

/* Variables and functions */
 int ENXIO ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int pinmux_config_grp (struct pinmux_softc*,char*,struct tegra_grp const*,struct pincfg*) ; 
 int pinmux_config_mux (struct pinmux_softc*,char*,struct tegra_mux const*,struct pincfg*) ; 
 struct tegra_grp* pinmux_search_grp (char*) ; 
 struct tegra_mux* pinmux_search_mux (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
pinmux_config_node(struct pinmux_softc *sc, char *pin_name, struct pincfg *cfg)
{
	const struct tegra_mux *mux;
	const struct tegra_grp *grp;
	uint32_t reg;
	int rv;

	/* Handle MIPI special case first */
	if (strcmp(pin_name, "dsi_b") == 0) {
		if (cfg->function == NULL) {
			/* nothing to set */
			return (0);
		}
		reg = bus_read_4(sc->mipi_mem_res, 0); /* register 0x820 */
		if (strcmp(cfg->function, "csi") == 0)
			reg &= ~(1 << 1);
		else if (strcmp(cfg->function, "dsi_b") == 0)
			reg |= (1 << 1);
		bus_write_4(sc->mipi_mem_res, 0, reg); /* register 0x820 */
	}

	/* Handle pin muxes */
	mux = pinmux_search_mux(pin_name);
	if (mux != NULL) {
		if (mux->gpio_num != -1) {
			/* XXXX TODO: Reserve gpio here */
		}
		rv = pinmux_config_mux(sc, pin_name, mux, cfg);
		return (rv);
	}

	/* Handle pin groups */
	grp = pinmux_search_grp(pin_name);
	if (grp != NULL) {
		rv = pinmux_config_grp(sc, pin_name, grp, cfg);
		return (rv);
	}

	device_printf(sc->dev, "Unknown pin: %s\n", pin_name);
	return (ENXIO);
}