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
struct mic_dma_chan {size_t head; int /*<<< orphan*/ * desc_ring; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {size_t max_xfer_size; } ;

/* Variables and functions */
 int mic_dma_avail_desc_ring_space (struct mic_dma_chan*,int) ; 
 int /*<<< orphan*/  mic_dma_hw_ring_inc_head (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  mic_dma_memcpy_desc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t min (size_t,size_t) ; 
 TYPE_1__* to_mic_dma_dev (struct mic_dma_chan*) ; 

__attribute__((used)) static int mic_dma_prog_memcpy_desc(struct mic_dma_chan *ch, dma_addr_t src,
				    dma_addr_t dst, size_t len)
{
	size_t current_transfer_len;
	size_t max_xfer_size = to_mic_dma_dev(ch)->max_xfer_size;
	/* 3 is added to make sure we have enough space for status desc */
	int num_desc = len / max_xfer_size + 3;
	int ret;

	if (len % max_xfer_size)
		num_desc++;

	ret = mic_dma_avail_desc_ring_space(ch, num_desc);
	if (ret < 0)
		return ret;
	do {
		current_transfer_len = min(len, max_xfer_size);
		mic_dma_memcpy_desc(&ch->desc_ring[ch->head],
				    src, dst, current_transfer_len);
		mic_dma_hw_ring_inc_head(ch);
		len -= current_transfer_len;
		dst = dst + current_transfer_len;
		src = src + current_transfer_len;
	} while (len > 0);
	return 0;
}