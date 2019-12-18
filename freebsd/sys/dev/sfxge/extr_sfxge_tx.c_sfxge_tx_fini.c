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
struct sfxge_softc {int txq_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  sfxge_tx_qfini (struct sfxge_softc*,int) ; 

void
sfxge_tx_fini(struct sfxge_softc *sc)
{
	int index;

	index = sc->txq_count;
	while (--index >= 0)
		sfxge_tx_qfini(sc, index);

	sc->txq_count = 0;
}