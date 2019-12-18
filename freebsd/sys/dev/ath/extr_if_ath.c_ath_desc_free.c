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
struct TYPE_2__ {scalar_t__ dd_desc_len; } ;
struct ath_softc {int /*<<< orphan*/  sc_txbuf_mgmt; TYPE_1__ sc_txdma_mgmt; int /*<<< orphan*/  sc_txbuf; TYPE_1__ sc_txdma; int /*<<< orphan*/  sc_bbuf; TYPE_1__ sc_bdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath_descdma_cleanup (struct ath_softc*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ath_desc_free(struct ath_softc *sc)
{

	if (sc->sc_bdma.dd_desc_len != 0)
		ath_descdma_cleanup(sc, &sc->sc_bdma, &sc->sc_bbuf);
	if (sc->sc_txdma.dd_desc_len != 0)
		ath_descdma_cleanup(sc, &sc->sc_txdma, &sc->sc_txbuf);
	if (sc->sc_txdma_mgmt.dd_desc_len != 0)
		ath_descdma_cleanup(sc, &sc->sc_txdma_mgmt,
		    &sc->sc_txbuf_mgmt);
}