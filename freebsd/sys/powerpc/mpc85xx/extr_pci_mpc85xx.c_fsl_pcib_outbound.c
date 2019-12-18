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
struct fsl_pcib_softc {int /*<<< orphan*/  sc_bsh; int /*<<< orphan*/  sc_bst; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_POTAR (int) ; 
 int /*<<< orphan*/  REG_POTEAR (int) ; 
 int /*<<< orphan*/  REG_POWAR (int) ; 
 int /*<<< orphan*/  REG_POWBAR (int) ; 
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_MEMORY 128 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ffsll (int) ; 

__attribute__((used)) static void
fsl_pcib_outbound(struct fsl_pcib_softc *sc, int wnd, int res, uint64_t start,
    uint64_t size, uint64_t pci_start)
{
	uint32_t attr, bar, tar;

	switch (res) {
	case SYS_RES_MEMORY:
		attr = 0x80044000 | (ffsll(size) - 2);
		break;
	case SYS_RES_IOPORT:
		attr = 0x80088000 | (ffsll(size) - 2);
		break;
	default:
		attr = 0x0004401f;
		break;
	}
	bar = start >> 12;
	tar = pci_start >> 12;

	bus_space_write_4(sc->sc_bst, sc->sc_bsh, REG_POTAR(wnd), tar);
	bus_space_write_4(sc->sc_bst, sc->sc_bsh, REG_POTEAR(wnd), 0);
	bus_space_write_4(sc->sc_bst, sc->sc_bsh, REG_POWBAR(wnd), bar);
	bus_space_write_4(sc->sc_bst, sc->sc_bsh, REG_POWAR(wnd), attr);
}