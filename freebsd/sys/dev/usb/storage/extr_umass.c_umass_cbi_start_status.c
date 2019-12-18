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
struct umass_softc {TYPE_1__ sc_transfer; int /*<<< orphan*/  sc_last_xfer_index; scalar_t__* sc_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_CMD_UNKNOWN ; 
 int /*<<< orphan*/  UMASS_T_CBI_COMMAND ; 
 size_t UMASS_T_CBI_STATUS ; 
 int /*<<< orphan*/  stub1 (struct umass_softc*,union ccb*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umass_transfer_start (struct umass_softc*,size_t) ; 

__attribute__((used)) static void
umass_cbi_start_status(struct umass_softc *sc)
{
	if (sc->sc_xfer[UMASS_T_CBI_STATUS]) {
		umass_transfer_start(sc, UMASS_T_CBI_STATUS);
	} else {
		union ccb *ccb = sc->sc_transfer.ccb;

		sc->sc_transfer.ccb = NULL;

		sc->sc_last_xfer_index = UMASS_T_CBI_COMMAND;

		(sc->sc_transfer.callback)
		    (sc, ccb, (sc->sc_transfer.data_len -
		    sc->sc_transfer.actlen), STATUS_CMD_UNKNOWN);
	}
}