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
typedef  int u_int ;
struct mv_pcib_softc {scalar_t__ sc_type; int /*<<< orphan*/  sc_bsh; int /*<<< orphan*/  sc_bst; } ;

/* Variables and functions */
 scalar_t__ MV_TYPE_PCI ; 
 int PCIE_REG_CFG_ADDR ; 
 int PCIE_REG_CFG_DATA ; 
 int PCI_CFG_BUS (int) ; 
 int PCI_CFG_DEV (int) ; 
 int PCI_CFG_ENA ; 
 int PCI_CFG_FUN (int) ; 
 int PCI_CFG_PCIE_REG (int) ; 
 int PCI_REG_CFG_ADDR ; 
 int PCI_REG_CFG_DATA ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bus_space_write_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  htole16 (int) ; 
 int htole32 (int) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcicfg_mtx ; 

__attribute__((used)) static void
mv_pcib_hw_cfgwrite(struct mv_pcib_softc *sc, u_int bus, u_int slot,
    u_int func, u_int reg, uint32_t data, int bytes)
{
	uint32_t addr, ca, cd;

	ca = (sc->sc_type != MV_TYPE_PCI) ?
	    PCIE_REG_CFG_ADDR : PCI_REG_CFG_ADDR;
	cd = (sc->sc_type != MV_TYPE_PCI) ?
	    PCIE_REG_CFG_DATA : PCI_REG_CFG_DATA;
	addr = PCI_CFG_ENA | PCI_CFG_BUS(bus) | PCI_CFG_DEV(slot) |
	    PCI_CFG_FUN(func) | PCI_CFG_PCIE_REG(reg);

	mtx_lock_spin(&pcicfg_mtx);
	bus_space_write_4(sc->sc_bst, sc->sc_bsh, ca, addr);

	switch (bytes) {
	case 1:
		bus_space_write_1(sc->sc_bst, sc->sc_bsh,
		    cd + (reg & 3), data);
		break;
	case 2:
		bus_space_write_2(sc->sc_bst, sc->sc_bsh,
		    cd + (reg & 2), htole16(data));
		break;
	case 4:
		bus_space_write_4(sc->sc_bst, sc->sc_bsh,
		    cd, htole32(data));
		break;
	}
	mtx_unlock_spin(&pcicfg_mtx);
}