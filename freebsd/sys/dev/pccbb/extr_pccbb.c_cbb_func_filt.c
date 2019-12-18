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
struct cbb_softc {scalar_t__ cardok; } ;
struct cbb_intrhand {int (* filt ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  arg; struct cbb_softc* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CBB_CARD_PRESENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CBB_SOCKET_STATE ; 
 int FILTER_HANDLED ; 
 int FILTER_STRAY ; 
 int /*<<< orphan*/  cbb_get (struct cbb_softc*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cbb_func_filt(void *arg)
{
	struct cbb_intrhand *ih = (struct cbb_intrhand *)arg;
	struct cbb_softc *sc = ih->sc;

	/*
	 * Make sure that the card is really there.
	 */
	if (!sc->cardok)
		return (FILTER_STRAY);
	if (!CBB_CARD_PRESENT(cbb_get(sc, CBB_SOCKET_STATE))) {
		sc->cardok = 0;
		return (FILTER_HANDLED);
	}

	/*
	 * nb: don't have to check for giant or not, since that's done in the
	 * ISR dispatch and one can't hold Giant in a filter anyway...
	 */
	return ((*ih->filt)(ih->arg));	
}