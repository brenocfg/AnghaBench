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
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct ath_softc {TYPE_1__ sc_btcoex; int /*<<< orphan*/  sc_ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath_descdma_cleanup (struct ath_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_hal_btcoex_mci_detach (int /*<<< orphan*/ ) ; 

int
ath_btcoex_mci_detach(struct ath_softc *sc)
{

	ath_hal_btcoex_mci_detach(sc->sc_ah);
	ath_descdma_cleanup(sc, &sc->sc_btcoex.buf, NULL);
	return (0);
}