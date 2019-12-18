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
typedef  unsigned int uint32_t ;
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
 unsigned int bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_space_read_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct thunder_pem_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 unsigned int le16toh (int /*<<< orphan*/ ) ; 
 unsigned int le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
thunder_pem_read_config(device_t dev, u_int bus, u_int slot,
    u_int func, u_int reg, int bytes)
{
	uint64_t offset;
	uint32_t data;
	struct thunder_pem_softc *sc;
	bus_space_tag_t	t;
	bus_space_handle_t h;

	if ((bus > PCI_BUSMAX) || (slot > PCI_SLOTMAX) ||
	    (func > PCI_FUNCMAX) || (reg > PCIE_REGMAX))
		return (~0U);

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
		data = bus_space_read_1(t, h, reg);
		break;
	case 2:
		data = le16toh(bus_space_read_2(t, h, reg));
		break;
	case 4:
		data = le32toh(bus_space_read_4(t, h, reg));
		break;
	default:
		data = ~0U;
		break;
	}

	bus_space_unmap(sc->reg_bst, h, PCIE_REGMAX);

	return (data);
}