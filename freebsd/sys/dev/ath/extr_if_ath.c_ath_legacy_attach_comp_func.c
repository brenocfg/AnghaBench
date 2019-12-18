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
struct ath_softc {int sc_txqsetup; int /*<<< orphan*/  sc_txtask; TYPE_1__* sc_cabq; } ;
struct TYPE_2__ {int axq_qnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ath_softc*) ; 
 int /*<<< orphan*/  ath_tx_proc ; 
 int /*<<< orphan*/  ath_tx_proc_q0 ; 
 int /*<<< orphan*/  ath_tx_proc_q0123 ; 

void
ath_legacy_attach_comp_func(struct ath_softc *sc)
{

	/*
	 * Special case certain configurations.  Note the
	 * CAB queue is handled by these specially so don't
	 * include them when checking the txq setup mask.
	 */
	switch (sc->sc_txqsetup &~ (1<<sc->sc_cabq->axq_qnum)) {
	case 0x01:
		TASK_INIT(&sc->sc_txtask, 0, ath_tx_proc_q0, sc);
		break;
	case 0x0f:
		TASK_INIT(&sc->sc_txtask, 0, ath_tx_proc_q0123, sc);
		break;
	default:
		TASK_INIT(&sc->sc_txtask, 0, ath_tx_proc, sc);
		break;
	}
}