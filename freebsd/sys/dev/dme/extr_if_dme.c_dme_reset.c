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
typedef  int u_int ;
struct dme_softc {scalar_t__ dme_txready; scalar_t__ dme_txbusy; TYPE_1__* dme_ifp; int /*<<< orphan*/  dme_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DME_NCR ; 
 int /*<<< orphan*/  DTR3 (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int NCR_LBK_MAC ; 
 int NCR_RST ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int dme_read_reg (struct dme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dme_write_reg (struct dme_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
dme_reset(struct dme_softc *sc)
{
	u_int ncr;

	/* Send a soft reset #1 */
	dme_write_reg(sc, DME_NCR, NCR_RST | NCR_LBK_MAC);
	DELAY(100); /* Wait for the MAC to reset */
	ncr = dme_read_reg(sc, DME_NCR);
	if (ncr & NCR_RST)
		device_printf(sc->dme_dev, "device did not complete first reset\n");

	/* Send a soft reset #2 per Application Notes v1.22 */
	dme_write_reg(sc, DME_NCR, 0);
	dme_write_reg(sc, DME_NCR, NCR_RST | NCR_LBK_MAC);
	DELAY(100); /* Wait for the MAC to reset */
	ncr = dme_read_reg(sc, DME_NCR);
	if (ncr & NCR_RST)
		device_printf(sc->dme_dev, "device did not complete second reset\n");

	/* Reset trasmit state */
	sc->dme_txbusy = 0;
	sc->dme_txready = 0;

	DTR3("dme_reset, flags %#x busy %d ready %d",
	    sc->dme_ifp ? sc->dme_ifp->if_drv_flags : 0,
	    sc->dme_txbusy, sc->dme_txready);
}