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
struct ag71xx_ring {TYPE_2__* buf; int /*<<< orphan*/  order; } ;
struct ag71xx {int /*<<< orphan*/  rx_buf_size; TYPE_1__* dev; struct ag71xx_ring rx_ring; } ;
struct TYPE_4__ {scalar_t__ rx_buf; int /*<<< orphan*/  dma_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_free_frag (scalar_t__) ; 

__attribute__((used)) static void ag71xx_ring_rx_clean(struct ag71xx *ag)
{
	struct ag71xx_ring *ring = &ag->rx_ring;
	int ring_size = BIT(ring->order);
	int i;

	if (!ring->buf)
		return;

	for (i = 0; i < ring_size; i++)
		if (ring->buf[i].rx_buf) {
			dma_unmap_single(&ag->dev->dev, ring->buf[i].dma_addr,
					 ag->rx_buf_size, DMA_FROM_DEVICE);
			skb_free_frag(ring->buf[i].rx_buf);
		}
}