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
typedef  scalar_t__ u_int ;
struct octopci_softc {int /*<<< orphan*/  sc_domain; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCTEON_FEATURE_PCIE ; 
 int /*<<< orphan*/  cvmx_pcie_config_read16 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cvmx_pcie_config_read32 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cvmx_pcie_config_read8 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cvmx_read64_uint16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_read64_uint32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_read64_uint8 (int /*<<< orphan*/ ) ; 
 struct octopci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octopci_cs_addr (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static uint32_t
octopci_read_config(device_t dev, u_int bus, u_int slot, u_int func, u_int reg,
    int bytes)
{
	struct octopci_softc *sc;
	uint64_t addr;
	uint32_t data;

	sc = device_get_softc(dev);

	if (octeon_has_feature(OCTEON_FEATURE_PCIE)) {
		if (bus == 0 && slot == 0 && func == 0)
			return ((uint32_t)-1);

		switch (bytes) {
		case 4:
			return (cvmx_pcie_config_read32(sc->sc_domain, bus, slot, func, reg));
		case 2:
			return (cvmx_pcie_config_read16(sc->sc_domain, bus, slot, func, reg));
		case 1:
			return (cvmx_pcie_config_read8(sc->sc_domain, bus, slot, func, reg));
		default:
			return ((uint32_t)-1);
		}
	}

	addr = octopci_cs_addr(bus, slot, func, reg);

	switch (bytes) {
	case 4:
		data = le32toh(cvmx_read64_uint32(addr));
		return (data);
	case 2:
		data = le16toh(cvmx_read64_uint16(addr));
		return (data);
	case 1:
		data = cvmx_read64_uint8(addr);
		return (data);
	default:
		return ((uint32_t)-1);
	}
}