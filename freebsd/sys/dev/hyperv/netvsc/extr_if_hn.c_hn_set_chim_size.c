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
struct hn_softc {int hn_tx_ring_cnt; TYPE_1__* hn_tx_ring; } ;
struct TYPE_2__ {int hn_chim_size; } ;

/* Variables and functions */

__attribute__((used)) static void
hn_set_chim_size(struct hn_softc *sc, int chim_size)
{
	int i;

	for (i = 0; i < sc->hn_tx_ring_cnt; ++i)
		sc->hn_tx_ring[i].hn_chim_size = chim_size;
}