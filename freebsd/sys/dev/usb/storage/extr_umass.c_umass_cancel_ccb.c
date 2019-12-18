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
typedef  union ccb {int dummy; } ccb ;
struct TYPE_2__ {scalar_t__ actlen; scalar_t__ data_len; int /*<<< orphan*/  (* callback ) (struct umass_softc*,union ccb*,scalar_t__,int /*<<< orphan*/ ) ;union ccb* ccb; } ;
struct umass_softc {TYPE_1__ sc_transfer; scalar_t__ sc_last_xfer_index; int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  STATUS_WIRE_FAILED ; 
 int /*<<< orphan*/  USB_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct umass_softc*,union ccb*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
umass_cancel_ccb(struct umass_softc *sc)
{
	union ccb *ccb;

	USB_MTX_ASSERT(&sc->sc_mtx, MA_OWNED);

	ccb = sc->sc_transfer.ccb;
	sc->sc_transfer.ccb = NULL;
	sc->sc_last_xfer_index = 0;

	if (ccb) {
		(sc->sc_transfer.callback)
		    (sc, ccb, (sc->sc_transfer.data_len -
		    sc->sc_transfer.actlen), STATUS_WIRE_FAILED);
	}
}