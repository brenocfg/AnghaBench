#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct otus_softc {int /*<<< orphan*/  sc_cmd; int /*<<< orphan*/  sc_cmd_waiting; int /*<<< orphan*/  sc_cmd_pending; int /*<<< orphan*/  sc_cmd_inactive; int /*<<< orphan*/  sc_cmd_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  OTUS_CMD_LIST_COUNT ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  otus_free_cmd_list (struct otus_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
otus_free_tx_cmd_list(struct otus_softc *sc)
{

	/*
	 * XXX TODO: something needs to wake up any pending/sleeping
	 * waiters!
	 */
	STAILQ_INIT(&sc->sc_cmd_active);
	STAILQ_INIT(&sc->sc_cmd_inactive);
	STAILQ_INIT(&sc->sc_cmd_pending);
	STAILQ_INIT(&sc->sc_cmd_waiting);

	otus_free_cmd_list(sc, sc->sc_cmd, OTUS_CMD_LIST_COUNT);
}