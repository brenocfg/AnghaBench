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
typedef  int u32 ;
struct descriptor {int control; int /*<<< orphan*/  req_count; int /*<<< orphan*/  data_address; } ;
struct context {int current_bus; TYPE_2__* ohci; } ;
typedef  int __le16 ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {TYPE_1__ card; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESCRIPTOR_BRANCH_ALWAYS ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int PAGE_MASK ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_range_for_cpu (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sync_it_packet_for_cpu(struct context *context,
					  struct descriptor *pd)
{
	__le16 control;
	u32 buffer_dma;

	/* only packets beginning with OUTPUT_MORE* have data buffers */
	if (pd->control & cpu_to_le16(DESCRIPTOR_BRANCH_ALWAYS))
		return;

	/* skip over the OUTPUT_MORE_IMMEDIATE descriptor */
	pd += 2;

	/*
	 * If the packet has a header, the first OUTPUT_MORE/LAST descriptor's
	 * data buffer is in the context program's coherent page and must not
	 * be synced.
	 */
	if ((le32_to_cpu(pd->data_address) & PAGE_MASK) ==
	    (context->current_bus          & PAGE_MASK)) {
		if (pd->control & cpu_to_le16(DESCRIPTOR_BRANCH_ALWAYS))
			return;
		pd++;
	}

	do {
		buffer_dma = le32_to_cpu(pd->data_address);
		dma_sync_single_range_for_cpu(context->ohci->card.device,
					      buffer_dma & PAGE_MASK,
					      buffer_dma & ~PAGE_MASK,
					      le16_to_cpu(pd->req_count),
					      DMA_TO_DEVICE);
		control = pd->control;
		pd++;
	} while (!(control & cpu_to_le16(DESCRIPTOR_BRANCH_ALWAYS)));
}