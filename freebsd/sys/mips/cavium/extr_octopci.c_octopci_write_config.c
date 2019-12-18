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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct octopci_softc {int /*<<< orphan*/  sc_domain; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCTEON_FEATURE_PCIE ; 
 int /*<<< orphan*/  cvmx_pcie_config_write16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_pcie_config_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_pcie_config_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write64_uint16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write64_uint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write64_uint8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct octopci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octopci_cs_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
octopci_write_config(device_t dev, u_int bus, u_int slot, u_int func,
    u_int reg, uint32_t data, int bytes)
{
	struct octopci_softc *sc;
	uint64_t addr;

	sc = device_get_softc(dev);

	if (octeon_has_feature(OCTEON_FEATURE_PCIE)) {
		switch (bytes) {
		case 4:
			cvmx_pcie_config_write32(sc->sc_domain, bus, slot, func, reg, data);
			return;
		case 2:
			cvmx_pcie_config_write16(sc->sc_domain, bus, slot, func, reg, data);
			return;
		case 1:
			cvmx_pcie_config_write8(sc->sc_domain, bus, slot, func, reg, data);
			return;
		default:
			return;
		}
	}

	addr = octopci_cs_addr(bus, slot, func, reg);

	switch (bytes) {
	case 4:
		cvmx_write64_uint32(addr, htole32(data));
		return;
	case 2:
		cvmx_write64_uint16(addr, htole16(data));
		return;
	case 1:
		cvmx_write64_uint8(addr, data);
		return;
	default:
		return;
	}
}