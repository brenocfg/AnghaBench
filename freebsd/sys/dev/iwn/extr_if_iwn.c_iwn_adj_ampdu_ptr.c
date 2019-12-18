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
struct iwn_tx_ring {int read; int cur; struct iwn_tx_data* data; } ;
struct iwn_tx_data {scalar_t__ remapped; int /*<<< orphan*/ * m; } ;
struct iwn_softc {int dummy; } ;

/* Variables and functions */
 int IWN_TX_RING_COUNT ; 

__attribute__((used)) static void
iwn_adj_ampdu_ptr(struct iwn_softc *sc, struct iwn_tx_ring *ring)
{
	int i;

	for (i = ring->read; i != ring->cur; i = (i + 1) % IWN_TX_RING_COUNT) {
		struct iwn_tx_data *data = &ring->data[i];

		if (data->m != NULL)
			break;

		data->remapped = 0;
	}

	ring->read = i;
}