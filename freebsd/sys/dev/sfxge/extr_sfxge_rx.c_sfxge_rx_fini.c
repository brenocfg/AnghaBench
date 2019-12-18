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
struct sfxge_softc {int rxq_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  sfxge_rx_qfini (struct sfxge_softc*,int) ; 

void
sfxge_rx_fini(struct sfxge_softc *sc)
{
	int index;

	index = sc->rxq_count;
	while (--index >= 0)
		sfxge_rx_qfini(sc, index);

	sc->rxq_count = 0;
}