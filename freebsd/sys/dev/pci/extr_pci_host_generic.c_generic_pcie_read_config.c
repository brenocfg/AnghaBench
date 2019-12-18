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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  unsigned int uint32_t ;
typedef  scalar_t__ u_int ;
struct generic_pcie_core_softc {scalar_t__ bus_start; scalar_t__ bus_end; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_ADDR_OFFSET (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ PCIE_REGMAX ; 
 scalar_t__ PCI_FUNCMAX ; 
 scalar_t__ PCI_SLOTMAX ; 
 unsigned int bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_read_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct generic_pcie_core_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 unsigned int le16toh (int /*<<< orphan*/ ) ; 
 unsigned int le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
generic_pcie_read_config(device_t dev, u_int bus, u_int slot,
    u_int func, u_int reg, int bytes)
{
	struct generic_pcie_core_softc *sc;
	bus_space_handle_t h;
	bus_space_tag_t	t;
	uint64_t offset;
	uint32_t data;

	sc = device_get_softc(dev);
	if ((bus < sc->bus_start) || (bus > sc->bus_end))
		return (~0U);
	if ((slot > PCI_SLOTMAX) || (func > PCI_FUNCMAX) ||
	    (reg > PCIE_REGMAX))
		return (~0U);

	offset = PCIE_ADDR_OFFSET(bus - sc->bus_start, slot, func, reg);
	t = sc->bst;
	h = sc->bsh;

	switch (bytes) {
	case 1:
		data = bus_space_read_1(t, h, offset);
		break;
	case 2:
		data = le16toh(bus_space_read_2(t, h, offset));
		break;
	case 4:
		data = le32toh(bus_space_read_4(t, h, offset));
		break;
	default:
		return (~0U);
	}

	return (data);
}