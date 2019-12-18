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
struct otus_softc {int /*<<< orphan*/ * sc_cmd; int /*<<< orphan*/  sc_cmd_inactive; int /*<<< orphan*/  sc_cmd_waiting; int /*<<< orphan*/  sc_cmd_pending; int /*<<< orphan*/  sc_cmd_active; } ;

/* Variables and functions */
 int OTUS_CMD_LIST_COUNT ; 
 int /*<<< orphan*/  OTUS_MAX_TXCMDSZ ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_cmd ; 
 int otus_alloc_cmd_list (struct otus_softc*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
otus_alloc_tx_cmd_list(struct otus_softc *sc)
{
	int error, i;

	error = otus_alloc_cmd_list(sc, sc->sc_cmd, OTUS_CMD_LIST_COUNT,
	    OTUS_MAX_TXCMDSZ);
	if (error != 0)
		return (error);

	STAILQ_INIT(&sc->sc_cmd_active);
	STAILQ_INIT(&sc->sc_cmd_inactive);
	STAILQ_INIT(&sc->sc_cmd_pending);
	STAILQ_INIT(&sc->sc_cmd_waiting);

	for (i = 0; i < OTUS_CMD_LIST_COUNT; i++)
		STAILQ_INSERT_HEAD(&sc->sc_cmd_inactive, &sc->sc_cmd[i],
		    next_cmd);

	return (0);
}