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
struct ath_softc {int /*<<< orphan*/  sc_rxbuf; TYPE_1__ sc_rxdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath_descdma_cleanup (struct ath_softc*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ath_legacy_dma_rxteardown(struct ath_softc *sc)
{

	if (sc->sc_rxdma.dd_desc_len != 0)
		ath_descdma_cleanup(sc, &sc->sc_rxdma, &sc->sc_rxbuf);
	return (0);
}