#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rt2560_softc {int dummy; } ;
struct rt2560_rx_ring {int count; scalar_t__ cur_decrypt; scalar_t__ next; scalar_t__ cur; int /*<<< orphan*/  desc_map; int /*<<< orphan*/  desc_dmat; TYPE_1__* data; TYPE_2__* desc; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {scalar_t__ drop; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  RT2560_RX_BUSY ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rt2560_reset_rx_ring(struct rt2560_softc *sc, struct rt2560_rx_ring *ring)
{
	int i;

	for (i = 0; i < ring->count; i++) {
		ring->desc[i].flags = htole32(RT2560_RX_BUSY);
		ring->data[i].drop = 0;
	}

	bus_dmamap_sync(ring->desc_dmat, ring->desc_map, BUS_DMASYNC_PREWRITE);

	ring->cur = ring->next = 0;
	ring->cur_decrypt = 0;
}