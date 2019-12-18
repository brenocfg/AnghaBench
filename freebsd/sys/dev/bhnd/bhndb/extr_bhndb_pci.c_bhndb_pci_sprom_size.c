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
struct bhndb_regwin {int /*<<< orphan*/  win_size; } ;
struct bhndb_pci_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  parent; } ;
typedef  int bus_size_t ;

/* Variables and functions */
 int BHNDB_PCI_SPROM_BLANK ; 
 int /*<<< orphan*/  BHNDB_PCI_SPROM_CONTROL ; 
#define  BHNDB_PCI_SPROM_SZ_16KB 131 
#define  BHNDB_PCI_SPROM_SZ_1KB 130 
#define  BHNDB_PCI_SPROM_SZ_4KB 129 
 int BHNDB_PCI_SPROM_SZ_MASK ; 
#define  BHNDB_PCI_SPROM_SZ_RESERVED 128 
 int MIN (int,int /*<<< orphan*/ ) ; 
 struct bhndb_regwin* bhndb_pci_sprom_regwin (struct bhndb_pci_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bus_size_t
bhndb_pci_sprom_size(struct bhndb_pci_softc *sc)
{
	const struct bhndb_regwin	*sprom_win;
	uint32_t			 sctl;
	bus_size_t			 sprom_sz;

	sprom_win = bhndb_pci_sprom_regwin(sc);

	/* PCI_V2 and later devices map SPROM/OTP via ChipCommon */
	if (sprom_win == NULL)
		return (0);

	/* Determine SPROM size */
	sctl = pci_read_config(sc->parent, BHNDB_PCI_SPROM_CONTROL, 4);
	if (sctl & BHNDB_PCI_SPROM_BLANK)
		return (0);

	switch (sctl & BHNDB_PCI_SPROM_SZ_MASK) {
	case BHNDB_PCI_SPROM_SZ_1KB:
		sprom_sz = (1 * 1024);
		break;

	case BHNDB_PCI_SPROM_SZ_4KB:
		sprom_sz = (4 * 1024);
		break;

	case BHNDB_PCI_SPROM_SZ_16KB:
		sprom_sz = (16 * 1024);
		break;

	case BHNDB_PCI_SPROM_SZ_RESERVED:
	default:
		device_printf(sc->dev, "invalid PCI sprom size 0x%x\n", sctl);
		return (0);
	}

	/* If the device has a larger SPROM than can be addressed via our SPROM
	 * register window, the SPROM image data will still be located within
	 * the window's addressable range */
	sprom_sz = MIN(sprom_sz, sprom_win->win_size);

	return (sprom_sz);
}