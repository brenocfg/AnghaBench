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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_int ;
struct thunder_pem_softc {int /*<<< orphan*/  reg_bst; scalar_t__ sli_window_base; int /*<<< orphan*/  pem_sli_base; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 scalar_t__ PCIE_REGMAX ; 
 scalar_t__ PCI_BUSMAX ; 
 scalar_t__ PCI_FUNCMAX ; 
 scalar_t__ PCI_SLOTMAX ; 
 scalar_t__ PEM_BUS_SHIFT ; 
 scalar_t__ PEM_FUNC_SHIFT ; 
 scalar_t__ PEM_SLOT_SHIFT ; 
 int /*<<< orphan*/  bus_space_map (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct thunder_pem_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
thunder_pem_write_config(device_t dev, u_int bus, u_int slot,
    u_int func, u_int reg, uint32_t val, int bytes)
{
	uint64_t offset;
	struct thunder_pem_softc *sc;
	bus_space_tag_t	t;
	bus_space_handle_t h;

	if ((bus > PCI_BUSMAX) || (slot > PCI_SLOTMAX) ||
	    (func > PCI_FUNCMAX) || (reg > PCIE_REGMAX))
		return;

	sc = device_get_softc(dev);

	/* Calculate offset */
	offset = (bus << PEM_BUS_SHIFT) | (slot << PEM_SLOT_SHIFT) |
	    (func << PEM_FUNC_SHIFT);
	t = sc->reg_bst;
	h = sc->pem_sli_base;

	bus_space_map(sc->reg_bst, sc->sli_window_base + offset,
	    PCIE_REGMAX, 0, &h);

	switch (bytes) {
	case 1:
		bus_space_write_1(t, h, reg, val);
		break;
	case 2:
		bus_space_write_2(t, h, reg, htole16(val));
		break;
	case 4:
		bus_space_write_4(t, h, reg, htole32(val));
		break;
	default:
		break;
	}

	bus_space_unmap(sc->reg_bst, h, PCIE_REGMAX);
}