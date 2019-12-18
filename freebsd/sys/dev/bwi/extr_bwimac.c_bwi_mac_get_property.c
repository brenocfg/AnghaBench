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
struct bwi_softc {int sc_bus_space; int /*<<< orphan*/  sc_dev; } ;
struct bwi_mac {int /*<<< orphan*/  mac_flags; struct bwi_softc* mac_sc; } ;
typedef  enum bwi_bus_space { ____Placeholder_bwi_bus_space } bwi_bus_space ;

/* Variables and functions */
 int BWI_BUS_SPACE_30BIT ; 
 int BWI_BUS_SPACE_32BIT ; 
 int BWI_BUS_SPACE_64BIT ; 
 int BWI_DBG_ATTACH ; 
 int BWI_DBG_MAC ; 
 int /*<<< orphan*/  BWI_MAC_F_BSWAP ; 
 int BWI_MAC_STATUS ; 
 int BWI_MAC_STATUS_BSWAP ; 
 int BWI_STATE_HI ; 
 int /*<<< orphan*/  BWI_STATE_HI_FLAGS_MASK ; 
 int BWI_STATE_HI_FLAG_64BIT ; 
 int BWI_TX32_CTRL ; 
 int BWI_TXRX32_CTRL_ADDRHI_MASK ; 
 int BWI_TXRX_CTRL_BASE ; 
 int CSR_READ_4 (struct bwi_softc*,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct bwi_softc*,int,int) ; 
 int /*<<< orphan*/  DPRINTF (struct bwi_softc*,int,char*,char*) ; 
 int ENXIO ; 
 int __SHIFTOUT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
bwi_mac_get_property(struct bwi_mac *mac)
{
	struct bwi_softc *sc = mac->mac_sc;
	enum bwi_bus_space old_bus_space;
	uint32_t val;

	/*
	 * Byte swap
	 */
	val = CSR_READ_4(sc, BWI_MAC_STATUS);
	if (val & BWI_MAC_STATUS_BSWAP) {
		DPRINTF(sc, BWI_DBG_MAC | BWI_DBG_ATTACH, "%s\n",
			"need byte swap");
		mac->mac_flags |= BWI_MAC_F_BSWAP;
	}

	/*
	 * DMA address space
	 */
	old_bus_space = sc->sc_bus_space;

	val = CSR_READ_4(sc, BWI_STATE_HI);
	if (__SHIFTOUT(val, BWI_STATE_HI_FLAGS_MASK) &
	    BWI_STATE_HI_FLAG_64BIT) {
		/* 64bit address */
		sc->sc_bus_space = BWI_BUS_SPACE_64BIT;
		DPRINTF(sc, BWI_DBG_MAC | BWI_DBG_ATTACH, "%s\n",
			"64bit bus space");
	} else {
		uint32_t txrx_reg = BWI_TXRX_CTRL_BASE + BWI_TX32_CTRL;

		CSR_WRITE_4(sc, txrx_reg, BWI_TXRX32_CTRL_ADDRHI_MASK);
		if (CSR_READ_4(sc, txrx_reg) & BWI_TXRX32_CTRL_ADDRHI_MASK) {
			/* 32bit address */
			sc->sc_bus_space = BWI_BUS_SPACE_32BIT;
			DPRINTF(sc, BWI_DBG_MAC | BWI_DBG_ATTACH, "%s\n",
				"32bit bus space");
		} else {
			/* 30bit address */
			sc->sc_bus_space = BWI_BUS_SPACE_30BIT;
			DPRINTF(sc, BWI_DBG_MAC | BWI_DBG_ATTACH, "%s\n",
				"30bit bus space");
		}
	}

	if (old_bus_space != 0 && old_bus_space != sc->sc_bus_space) {
		device_printf(sc->sc_dev, "MACs bus space mismatch!\n");
		return ENXIO;
	}
	return 0;
}