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
typedef  int u64 ;
struct mic_dma_chan {int /*<<< orphan*/ * desc_ring; int /*<<< orphan*/  desc_ring_micpa; int /*<<< orphan*/  tx_array; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  MIC_DMA_ALIGN_BYTES ; 
 int MIC_DMA_DESC_RX_SIZE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_mbus_device (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mic_dma_free_desc_ring(struct mic_dma_chan *ch)
{
	u64 desc_ring_size = MIC_DMA_DESC_RX_SIZE * sizeof(*ch->desc_ring);

	vfree(ch->tx_array);
	desc_ring_size = ALIGN(desc_ring_size, MIC_DMA_ALIGN_BYTES);
	dma_unmap_single(&to_mbus_device(ch)->dev, ch->desc_ring_micpa,
			 desc_ring_size, DMA_BIDIRECTIONAL);
	kfree(ch->desc_ring);
	ch->desc_ring = NULL;
}