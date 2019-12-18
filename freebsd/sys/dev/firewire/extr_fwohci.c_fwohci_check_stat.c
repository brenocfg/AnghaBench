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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct fwohci_softc {int intmask; int /*<<< orphan*/  itstat; int /*<<< orphan*/  irstat; int /*<<< orphan*/  intstat; TYPE_1__ fc; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int FILTER_STRAY ; 
 int /*<<< orphan*/  FWOHCI_INTSTAT ; 
 int /*<<< orphan*/  FWOHCI_INTSTATCLR ; 
 int /*<<< orphan*/  FW_GLOCK_ASSERT (TYPE_1__*) ; 
 int OHCI_INT_DMA_IR ; 
 int OHCI_INT_DMA_IT ; 
 int OHCI_INT_PHY_BUS_R ; 
 int /*<<< orphan*/  OHCI_IR_STAT ; 
 int /*<<< orphan*/  OHCI_IR_STATCLR ; 
 int /*<<< orphan*/  OHCI_IT_STAT ; 
 int /*<<< orphan*/  OHCI_IT_STATCLR ; 
 int OREAD (struct fwohci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OWRITE (struct fwohci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_set_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bus_child_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fwohci_intr_core (struct fwohci_softc*,int,int) ; 

__attribute__((used)) static int
fwohci_check_stat(struct fwohci_softc *sc)
{
	uint32_t stat, irstat, itstat;

	FW_GLOCK_ASSERT(&sc->fc);
	stat = OREAD(sc, FWOHCI_INTSTAT);
	if (stat == 0xffffffff) {
		if (!bus_child_present(sc->fc.dev))
			return (FILTER_HANDLED);
		device_printf(sc->fc.dev, "device physically ejected?\n");
		return (FILTER_STRAY);
	}
	if (stat)
		OWRITE(sc, FWOHCI_INTSTATCLR, stat & ~OHCI_INT_PHY_BUS_R);

	stat &= sc->intmask;
	if (stat == 0)
		return (FILTER_STRAY);

	atomic_set_int(&sc->intstat, stat);
	if (stat & OHCI_INT_DMA_IR) {
		irstat = OREAD(sc, OHCI_IR_STAT);
		OWRITE(sc, OHCI_IR_STATCLR, irstat);
		atomic_set_int(&sc->irstat, irstat);
	}
	if (stat & OHCI_INT_DMA_IT) {
		itstat = OREAD(sc, OHCI_IT_STAT);
		OWRITE(sc, OHCI_IT_STATCLR, itstat);
		atomic_set_int(&sc->itstat, itstat);
	}

	fwohci_intr_core(sc, stat, -1);
	return (FILTER_HANDLED);
}