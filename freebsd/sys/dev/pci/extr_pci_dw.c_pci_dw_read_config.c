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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  scalar_t__ u_int ;
struct resource {int dummy; } ;
struct pci_dw_softc {scalar_t__ root_bus; scalar_t__ sub_bus; struct resource* cfg_res; int /*<<< orphan*/  cfg_size; int /*<<< orphan*/  cfg_pa; struct resource* dbi_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IATU_CFG_BUS (scalar_t__) ; 
 int IATU_CFG_FUNC (scalar_t__) ; 
 int IATU_CFG_SLOT (scalar_t__) ; 
 int IATU_CTRL1_TYPE_CFG0 ; 
 int IATU_CTRL1_TYPE_CFG1 ; 
 scalar_t__ PCI_FUNCMAX ; 
 scalar_t__ PCI_REGMAX ; 
 scalar_t__ PCI_SLOTMAX ; 
 int bus_read_1 (struct resource*,scalar_t__) ; 
 int bus_read_2 (struct resource*,scalar_t__) ; 
 int bus_read_4 (struct resource*,scalar_t__) ; 
 struct pci_dw_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dw_check_dev (struct pci_dw_softc*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int pci_dw_map_out_atu (struct pci_dw_softc*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
pci_dw_read_config(device_t dev, u_int bus, u_int slot,
    u_int func, u_int reg, int bytes)
{
	struct pci_dw_softc *sc;
	struct resource	*res;
	uint32_t data;
	uint64_t addr;
	int type, rv;

	sc = device_get_softc(dev);

	if (!pci_dw_check_dev(sc, bus, slot, func, reg))
		return (0xFFFFFFFFU);

	if ((slot > PCI_SLOTMAX) || (func > PCI_FUNCMAX) ||
	    (reg > PCI_REGMAX))
		return (0xFFFFFFFFU);

	if (bus == sc->root_bus) {
		res = (sc->dbi_res);
	} else {
		addr = IATU_CFG_BUS(bus) | IATU_CFG_SLOT(slot) |
		    IATU_CFG_FUNC(func);
		if (bus == sc->sub_bus)
			type = IATU_CTRL1_TYPE_CFG0;
		else
			type = IATU_CTRL1_TYPE_CFG1;
		rv = pci_dw_map_out_atu(sc, 1, type,
		    sc->cfg_pa, addr, sc->cfg_size);
		if (rv != 0)
			return (0xFFFFFFFFU);
		res = sc->cfg_res;
	}

	switch (bytes) {
	case 1:
		data = bus_read_1(res, reg);
		break;
	case 2:
		data = bus_read_2(res, reg);
		break;
	case 4:
		data = bus_read_4(res, reg);
		break;
	default:
		data =  0xFFFFFFFFU;
	}

	return (data);

}