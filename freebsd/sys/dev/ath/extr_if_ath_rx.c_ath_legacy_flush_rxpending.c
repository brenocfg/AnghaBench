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
struct ath_softc {TYPE_1__* sc_rxedma; } ;
struct TYPE_2__ {int /*<<< orphan*/ * m_rxpending; } ;

/* Variables and functions */
 size_t HAL_RX_QUEUE_HP ; 
 size_t HAL_RX_QUEUE_LP ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ath_legacy_flush_rxpending(struct ath_softc *sc)
{

	/* XXX ATH_RX_LOCK_ASSERT(sc); */

	if (sc->sc_rxedma[HAL_RX_QUEUE_LP].m_rxpending != NULL) {
		m_freem(sc->sc_rxedma[HAL_RX_QUEUE_LP].m_rxpending);
		sc->sc_rxedma[HAL_RX_QUEUE_LP].m_rxpending = NULL;
	}
	if (sc->sc_rxedma[HAL_RX_QUEUE_HP].m_rxpending != NULL) {
		m_freem(sc->sc_rxedma[HAL_RX_QUEUE_HP].m_rxpending);
		sc->sc_rxedma[HAL_RX_QUEUE_HP].m_rxpending = NULL;
	}
}