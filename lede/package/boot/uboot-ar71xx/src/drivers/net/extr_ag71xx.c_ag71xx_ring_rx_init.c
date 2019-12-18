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
typedef  void* u32 ;
struct ag71xx_ring {unsigned int desc_size; scalar_t__ curr; TYPE_1__* buf; scalar_t__ descs_dma; } ;
struct ag71xx {struct ag71xx_ring rx_ring; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl; void* data; void* next; } ;
struct TYPE_3__ {TYPE_2__* desc; } ;

/* Variables and functions */
 unsigned int AG71XX_RX_RING_SIZE ; 
 int /*<<< orphan*/  DBG (char*,TYPE_2__*,void*) ; 
 int /*<<< orphan*/  DESC_EMPTY ; 
 scalar_t__* NetRxPackets ; 
 scalar_t__ virt_to_phys (scalar_t__) ; 

__attribute__((used)) static int ag71xx_ring_rx_init(struct ag71xx *ag)
{
	struct ag71xx_ring *ring = &ag->rx_ring;
	unsigned int i;

	for (i = 0; i < AG71XX_RX_RING_SIZE; i++) {
		ring->buf[i].desc->next = (u32) virt_to_phys((ring->descs_dma +
			ring->desc_size * ((i + 1) % AG71XX_RX_RING_SIZE)));

		DBG("ag71xx: RX desc at %p, next is %08x\n",
			ring->buf[i].desc,
			ring->buf[i].desc->next);
	}

	for (i = 0; i < AG71XX_RX_RING_SIZE; i++) {
		ring->buf[i].desc->data = (u32) virt_to_phys(NetRxPackets[i]);
		ring->buf[i].desc->ctrl = DESC_EMPTY;
	}

	ring->curr = 0;

	return 0;
}