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
 int bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_space_read_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcicfg_mtx ; 

__attribute__((used)) static uint32_t
mv_pcib_hw_cfgread(struct mv_pcib_softc *sc, u_int bus, u_int slot,
    u_int func, u_int reg, int bytes)
{
	uint32_t addr, data, ca, cd;

	ca = (sc->sc_type != MV_TYPE_PCI) ?
	    PCIE_REG_CFG_ADDR : PCI_REG_CFG_ADDR;
	cd = (sc->sc_type != MV_TYPE_PCI) ?
	    PCIE_REG_CFG_DATA : PCI_REG_CFG_DATA;
	addr = PCI_CFG_ENA | PCI_CFG_BUS(bus) | PCI_CFG_DEV(slot) |
	    PCI_CFG_FUN(func) | PCI_CFG_PCIE_REG(reg);

	mtx_lock_spin(&pcicfg_mtx);
	bus_space_write_4(sc->sc_bst, sc->sc_bsh, ca, addr);

	data = ~0;
	switch (bytes) {
	case 1:
		data = bus_space_read_1(sc->sc_bst, sc->sc_bsh,
		    cd + (reg & 3));
		break;
	case 2:
		data = le16toh(bus_space_read_2(sc->sc_bst, sc->sc_bsh,
		    cd + (reg & 2)));
		break;
	case 4:
		data = le32toh(bus_space_read_4(sc->sc_bst, sc->sc_bsh,
		    cd));
		break;
	}
	mtx_unlock_spin(&pcicfg_mtx);
	return (data);
}