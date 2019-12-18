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
struct mic_dma_chan {size_t head; int /*<<< orphan*/  status_dest_micpa; int /*<<< orphan*/ * desc_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  mic_dma_hw_ring_inc_head (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  mic_dma_prep_status_desc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mic_dma_prog_intr(struct mic_dma_chan *ch)
{
	mic_dma_prep_status_desc(&ch->desc_ring[ch->head], 0,
				 ch->status_dest_micpa, false);
	mic_dma_hw_ring_inc_head(ch);
	mic_dma_prep_status_desc(&ch->desc_ring[ch->head], 0,
				 ch->status_dest_micpa, true);
	mic_dma_hw_ring_inc_head(ch);
}