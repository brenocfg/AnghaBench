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
struct dme_softc {int dme_txlen; int dme_txbusy; scalar_t__ dme_txready; TYPE_1__* dme_ifp; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DME_ASSERT_LOCKED (struct dme_softc*) ; 
 int /*<<< orphan*/  DME_ISR ; 
 int /*<<< orphan*/  DME_TCR ; 
 int /*<<< orphan*/  DME_TXPLH ; 
 int /*<<< orphan*/  DME_TXPLL ; 
 int /*<<< orphan*/  DTR3 (char*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  KASSERT (scalar_t__,char*) ; 
 int TCR_TXREQ ; 
 int /*<<< orphan*/  dme_read_reg (struct dme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dme_write_reg (struct dme_softc*,int /*<<< orphan*/ ,int) ; 

void
dme_transmit(struct dme_softc *sc)
{

	DME_ASSERT_LOCKED(sc);
	KASSERT(sc->dme_txready, ("transmit without txready"));

	dme_write_reg(sc, DME_TXPLL, sc->dme_txlen & 0xff);
	dme_write_reg(sc, DME_TXPLH, (sc->dme_txlen >> 8) & 0xff );

	/* Request to send the packet */
	dme_read_reg(sc, DME_ISR);

	dme_write_reg(sc, DME_TCR, TCR_TXREQ);

	sc->dme_txready = 0;
	sc->dme_txbusy = 1;
	DTR3("dme_transmit done, flags %#x busy %d ready %d",
	    sc->dme_ifp->if_drv_flags, sc->dme_txbusy, sc->dme_txready);
}