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
struct bce_softc {int bce_flags; int link_width; int link_speed; int bus_speed_mhz; char* bce_bc_ver; int rx_pages; int tx_pages; int pg_pages; int bce_phy_flags; char* bce_mfw_ver; int bce_rx_quick_cons_trip_int; int bce_rx_quick_cons_trip; int bce_rx_ticks_int; int bce_rx_ticks; int bce_tx_quick_cons_trip_int; int bce_tx_quick_cons_trip; int bce_tx_ticks_int; int bce_tx_ticks; int /*<<< orphan*/  bce_chipid; } ;

/* Variables and functions */
 int BCE_CHIP_ID (struct bce_softc*) ; 
 int BCE_MFW_ENABLE_FLAG ; 
 int BCE_PCIE_FLAG ; 
 int BCE_PCIX_FLAG ; 
 int BCE_PCI_32BIT_FLAG ; 
 int BCE_PHY_2_5G_CAPABLE_FLAG ; 
 int BCE_PHY_REMOTE_CAP_FLAG ; 
 int BCE_PHY_REMOTE_PORT_FIBER_FLAG ; 
 int /*<<< orphan*/  BCE_PRINTF (char*,int /*<<< orphan*/ ) ; 
 int BCE_USING_MSIX_FLAG ; 
 int BCE_USING_MSI_FLAG ; 
 int /*<<< orphan*/  BCE_VERBOSE_LOAD ; 
 int /*<<< orphan*/  DBENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBEXIT (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 scalar_t__ bce_hdr_split ; 
 scalar_t__ bce_verbose ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
bce_print_adapter_info(struct bce_softc *sc)
{
	int i = 0;

	DBENTER(BCE_VERBOSE_LOAD);

	if (bce_verbose || bootverbose) {
		BCE_PRINTF("ASIC (0x%08X); ", sc->bce_chipid);
		printf("Rev (%c%d); ", ((BCE_CHIP_ID(sc) & 0xf000) >>
		    12) + 'A', ((BCE_CHIP_ID(sc) & 0x0ff0) >> 4));


		/* Bus info. */
		if (sc->bce_flags & BCE_PCIE_FLAG) {
			printf("Bus (PCIe x%d, ", sc->link_width);
			switch (sc->link_speed) {
			case 1: printf("2.5Gbps); "); break;
			case 2:	printf("5Gbps); "); break;
			default: printf("Unknown link speed); ");
			}
		} else {
			printf("Bus (PCI%s, %s, %dMHz); ",
			    ((sc->bce_flags & BCE_PCIX_FLAG) ? "-X" : ""),
			    ((sc->bce_flags & BCE_PCI_32BIT_FLAG) ?
			    "32-bit" : "64-bit"), sc->bus_speed_mhz);
		}

		/* Firmware version and device features. */
		printf("B/C (%s); Bufs (RX:%d;TX:%d;PG:%d); Flags (",
		    sc->bce_bc_ver,	sc->rx_pages, sc->tx_pages,
		    (bce_hdr_split == TRUE ? sc->pg_pages: 0));

		if (bce_hdr_split == TRUE) {
			printf("SPLT");
			i++;
		}

		if (sc->bce_flags & BCE_USING_MSI_FLAG) {
			if (i > 0) printf("|");
			printf("MSI"); i++;
		}

		if (sc->bce_flags & BCE_USING_MSIX_FLAG) {
			if (i > 0) printf("|");
			printf("MSI-X"); i++;
		}

		if (sc->bce_phy_flags & BCE_PHY_2_5G_CAPABLE_FLAG) {
			if (i > 0) printf("|");
			printf("2.5G"); i++;
		}

		if (sc->bce_phy_flags & BCE_PHY_REMOTE_CAP_FLAG) {
			if (i > 0) printf("|");
			printf("Remote PHY(%s)",
			    sc->bce_phy_flags & BCE_PHY_REMOTE_PORT_FIBER_FLAG ?
			    "FIBER" : "TP"); i++;
		}

		if (sc->bce_flags & BCE_MFW_ENABLE_FLAG) {
			if (i > 0) printf("|");
			printf("MFW); MFW (%s)\n", sc->bce_mfw_ver);
		} else {
			printf(")\n");
		}

		printf("Coal (RX:%d,%d,%d,%d; TX:%d,%d,%d,%d)\n",
		    sc->bce_rx_quick_cons_trip_int,
		    sc->bce_rx_quick_cons_trip,
		    sc->bce_rx_ticks_int,
		    sc->bce_rx_ticks,
		    sc->bce_tx_quick_cons_trip_int,
		    sc->bce_tx_quick_cons_trip,
		    sc->bce_tx_ticks_int,
		    sc->bce_tx_ticks);

	}

	DBEXIT(BCE_VERBOSE_LOAD);
}