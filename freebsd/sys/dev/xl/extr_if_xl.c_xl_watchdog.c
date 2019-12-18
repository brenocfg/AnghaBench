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
typedef  int u_int16_t ;
struct TYPE_2__ {scalar_t__ xl_tx_cnt; int /*<<< orphan*/ * xl_tx_head; } ;
struct xl_softc {scalar_t__ xl_wdog_timer; scalar_t__ xl_type; int /*<<< orphan*/  xl_dev; TYPE_1__ xl_cdata; struct ifnet* xl_ifp; } ;
struct ifnet {int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int CSR_READ_2 (struct xl_softc*,int /*<<< orphan*/ ) ; 
 int EJUSTRETURN ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XL_LOCK_ASSERT (struct xl_softc*) ; 
 int XL_MEDIASTAT_CARRIER ; 
 int /*<<< orphan*/  XL_SEL_WIN (int) ; 
 scalar_t__ XL_TYPE_905B ; 
 int /*<<< orphan*/  XL_W4_MEDIA_STATUS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xl_init_locked (struct xl_softc*) ; 
 int /*<<< orphan*/  xl_rxeof (struct xl_softc*) ; 
 int /*<<< orphan*/  xl_start_90xB_locked (struct ifnet*) ; 
 int /*<<< orphan*/  xl_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  xl_txeoc (struct xl_softc*) ; 
 int /*<<< orphan*/  xl_txeof (struct xl_softc*) ; 
 int /*<<< orphan*/  xl_txeof_90xB (struct xl_softc*) ; 

__attribute__((used)) static int
xl_watchdog(struct xl_softc *sc)
{
	struct ifnet		*ifp = sc->xl_ifp;
	u_int16_t		status = 0;
	int			misintr;

	XL_LOCK_ASSERT(sc);

	if (sc->xl_wdog_timer == 0 || --sc->xl_wdog_timer != 0)
		return (0);

	xl_rxeof(sc);
	xl_txeoc(sc);
	misintr = 0;
	if (sc->xl_type == XL_TYPE_905B) {
		xl_txeof_90xB(sc);
		if (sc->xl_cdata.xl_tx_cnt == 0)
			misintr++;
	} else {
		xl_txeof(sc);
		if (sc->xl_cdata.xl_tx_head == NULL)
			misintr++;
	}
	if (misintr != 0) {
		device_printf(sc->xl_dev,
		    "watchdog timeout (missed Tx interrupts) -- recovering\n");
		return (0);
	}

	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
	XL_SEL_WIN(4);
	status = CSR_READ_2(sc, XL_W4_MEDIA_STATUS);
	device_printf(sc->xl_dev, "watchdog timeout\n");

	if (status & XL_MEDIASTAT_CARRIER)
		device_printf(sc->xl_dev,
		    "no carrier - transceiver cable problem?\n");

	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	xl_init_locked(sc);

	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd)) {
		if (sc->xl_type == XL_TYPE_905B)
			xl_start_90xB_locked(ifp);
		else
			xl_start_locked(ifp);
	}

	return (EJUSTRETURN);
}