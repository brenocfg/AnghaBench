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
struct otus_tx_cmd {int dummy; } ;
struct otus_softc {int /*<<< orphan*/  sc_cmd_inactive; } ;

/* Variables and functions */
 int /*<<< orphan*/  OTUS_LOCK_ASSERT (struct otus_softc*) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct otus_tx_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_cmd ; 

__attribute__((used)) static void
otus_free_txcmd(struct otus_softc *sc, struct otus_tx_cmd *bf)
{

	OTUS_LOCK_ASSERT(sc);
	STAILQ_INSERT_TAIL(&sc->sc_cmd_inactive, bf, next_cmd);
}