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
typedef  int /*<<< orphan*/  u_int ;
struct tegra_pcib_softc {int cfg_base_addr; int cfg_cur_offs; int /*<<< orphan*/  dev; int /*<<< orphan*/  cfg_handle; int /*<<< orphan*/  bus_tag; } ;
typedef  int bus_size_t ;

/* Variables and functions */
 int PCI_CFG_BUS (int /*<<< orphan*/ ) ; 
 int PCI_CFG_DEV (int /*<<< orphan*/ ) ; 
 int PCI_CFG_EXT_REG (int /*<<< orphan*/ ) ; 
 int PCI_CFG_FUN (int /*<<< orphan*/ ) ; 
 int bus_space_map (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
tegra_pcbib_map_cfg(struct tegra_pcib_softc *sc, u_int bus, u_int slot,
    u_int func, u_int reg)
{
	bus_size_t offs;
	int rv;

	offs = sc->cfg_base_addr;
	offs |= PCI_CFG_BUS(bus) | PCI_CFG_DEV(slot) | PCI_CFG_FUN(func) |
	    PCI_CFG_EXT_REG(reg);
	if ((sc->cfg_handle != 0) && (sc->cfg_cur_offs == offs))
		return (0);
	if (sc->cfg_handle != 0)
		bus_space_unmap(sc->bus_tag, sc->cfg_handle, 0x800);

	rv = bus_space_map(sc->bus_tag, offs, 0x800, 0, &sc->cfg_handle);
	if (rv != 0)
		device_printf(sc->dev, "Cannot map config space\n");
	else
		sc->cfg_cur_offs = offs;
	return (rv);
}