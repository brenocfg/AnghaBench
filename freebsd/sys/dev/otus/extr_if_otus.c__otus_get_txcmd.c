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
 struct otus_tx_cmd* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_cmd ; 

__attribute__((used)) static struct otus_tx_cmd *
_otus_get_txcmd(struct otus_softc *sc)
{
	struct otus_tx_cmd *bf;

	bf = STAILQ_FIRST(&sc->sc_cmd_inactive);
	if (bf != NULL)
		STAILQ_REMOVE_HEAD(&sc->sc_cmd_inactive, next_cmd);
	else
		bf = NULL;
	return (bf);
}