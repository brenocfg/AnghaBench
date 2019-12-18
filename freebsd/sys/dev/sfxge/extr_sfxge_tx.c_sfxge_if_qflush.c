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
struct sfxge_softc {unsigned int txq_count; int /*<<< orphan*/ * txq; } ;
struct ifnet {struct sfxge_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  sfxge_tx_qdpl_flush (int /*<<< orphan*/ ) ; 

void
sfxge_if_qflush(struct ifnet *ifp)
{
	struct sfxge_softc *sc;
	unsigned int i;

	sc = ifp->if_softc;

	for (i = 0; i < sc->txq_count; i++)
		sfxge_tx_qdpl_flush(sc->txq[i]);
}