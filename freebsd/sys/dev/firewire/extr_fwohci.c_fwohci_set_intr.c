#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct fwohci_softc {int /*<<< orphan*/  intmask; TYPE_1__ fc; } ;
struct firewire_comm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWOHCI_INTMASK ; 
 int /*<<< orphan*/  FWOHCI_INTMASKCLR ; 
 int /*<<< orphan*/  OHCI_INT_EN ; 
 int /*<<< orphan*/  OWRITE (struct fwohci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ firewire_debug ; 

__attribute__((used)) static void
fwohci_set_intr(struct firewire_comm *fc, int enable)
{
	struct fwohci_softc *sc;

	sc = (struct fwohci_softc *)fc;
	if (firewire_debug)
		device_printf(sc->fc.dev, "fwohci_set_intr: %d\n", enable);
	if (enable) {
		sc->intmask |= OHCI_INT_EN;
		OWRITE(sc, FWOHCI_INTMASK, OHCI_INT_EN);
	} else {
		sc->intmask &= ~OHCI_INT_EN;
		OWRITE(sc, FWOHCI_INTMASKCLR, OHCI_INT_EN);
	}
}