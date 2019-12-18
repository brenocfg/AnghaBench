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
typedef  int uint32_t ;
typedef  scalar_t__ u_int ;
struct tegra_pcib_softc {int /*<<< orphan*/  bus_tag; int /*<<< orphan*/  cfg_handle; TYPE_1__** ports; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
struct TYPE_2__ {scalar_t__ port_idx; int /*<<< orphan*/  cfg_handle; } ;

/* Variables and functions */
 int PCI_CFG_BASE_REG (scalar_t__) ; 
 int TEGRA_PCIB_MAX_PORTS ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct tegra_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int tegra_pcbib_map_cfg (struct tegra_pcib_softc*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
tegra_pcib_write_config(device_t dev, u_int bus, u_int slot, u_int func,
    u_int reg, uint32_t val, int bytes)
{
	struct tegra_pcib_softc *sc;
	bus_space_handle_t hndl;
	uint32_t off;
	uint32_t val2;
	int rv, i;

	sc = device_get_softc(dev);
	if (bus == 0) {
		if (func != 0)
			return;
		for (i = 0; i < TEGRA_PCIB_MAX_PORTS; i++) {
			if ((sc->ports[i] != NULL) &&
			    (sc->ports[i]->port_idx == slot)) {
				hndl = sc->ports[i]->cfg_handle;
				off = reg & 0xFFF;
				break;
			}
		}
		if (i >= TEGRA_PCIB_MAX_PORTS)
			return;
	} else {
		rv = tegra_pcbib_map_cfg(sc, bus, slot, func, reg);
		if (rv != 0)
			return;
		hndl = sc->cfg_handle;
		off = PCI_CFG_BASE_REG(reg);
	}

	switch (bytes) {
	case 4:
		bus_space_write_4(sc->bus_tag, hndl, off, val);
		break;
	case 2:
		val2 = bus_space_read_4(sc->bus_tag, hndl, off & ~3);
		val2 &= ~(0xffff << ((off & 3) << 3));
		val2 |= ((val & 0xffff) << ((off & 3) << 3));
		bus_space_write_4(sc->bus_tag, hndl, off & ~3, val2);
		break;
	case 1:
		val2 = bus_space_read_4(sc->bus_tag, hndl, off & ~3);
		val2 &= ~(0xff << ((off & 3) << 3));
		val2 |= ((val & 0xff) << ((off & 3) << 3));
		bus_space_write_4(sc->bus_tag, hndl, off & ~3, val2);
		break;
	}
}