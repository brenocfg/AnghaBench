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
struct ar_context {scalar_t__* pages; TYPE_2__* ohci; int /*<<< orphan*/  buffer; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {TYPE_1__ card; } ;

/* Variables and functions */
 unsigned int AR_BUFFERS ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __free_page (scalar_t__) ; 
 int /*<<< orphan*/  ar_buffer_bus (struct ar_context*,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar_context_release(struct ar_context *ctx)
{
	unsigned int i;

	vunmap(ctx->buffer);

	for (i = 0; i < AR_BUFFERS; i++)
		if (ctx->pages[i]) {
			dma_unmap_page(ctx->ohci->card.device,
				       ar_buffer_bus(ctx, i),
				       PAGE_SIZE, DMA_FROM_DEVICE);
			__free_page(ctx->pages[i]);
		}
}