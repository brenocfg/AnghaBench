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
typedef  int /*<<< orphan*/  u32 ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct fw_ohci {scalar_t__ misc_buffer_bus; struct descriptor* misc_buffer; TYPE_1__ card; } ;
struct descriptor {void* branch_address; void* data_address; void* control; void* req_count; } ;
struct ar_context {scalar_t__ descriptors_bus; struct descriptor* descriptors; int /*<<< orphan*/  buffer; struct page** pages; int /*<<< orphan*/  tasklet; struct fw_ohci* ohci; int /*<<< orphan*/  regs; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct page**) ; 
 int AR_BUFFERS ; 
 int AR_WRAPAROUND_PAGES ; 
 int DESCRIPTOR_BRANCH_ALWAYS ; 
 int DESCRIPTOR_INPUT_MORE ; 
 int DESCRIPTOR_STATUS ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int GFP_DMA32 ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VM_MAP ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int) ; 
 scalar_t__ ar_buffer_bus (struct ar_context*,unsigned int) ; 
 int /*<<< orphan*/  ar_context_release (struct ar_context*) ; 
 int /*<<< orphan*/  ar_context_tasklet ; 
 int ar_next_buffer_index (unsigned int) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  vmap (struct page**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ar_context_init(struct ar_context *ctx, struct fw_ohci *ohci,
			   unsigned int descriptors_offset, u32 regs)
{
	unsigned int i;
	dma_addr_t dma_addr;
	struct page *pages[AR_BUFFERS + AR_WRAPAROUND_PAGES];
	struct descriptor *d;

	ctx->regs        = regs;
	ctx->ohci        = ohci;
	tasklet_init(&ctx->tasklet, ar_context_tasklet, (unsigned long)ctx);

	for (i = 0; i < AR_BUFFERS; i++) {
		ctx->pages[i] = alloc_page(GFP_KERNEL | GFP_DMA32);
		if (!ctx->pages[i])
			goto out_of_memory;
		dma_addr = dma_map_page(ohci->card.device, ctx->pages[i],
					0, PAGE_SIZE, DMA_FROM_DEVICE);
		if (dma_mapping_error(ohci->card.device, dma_addr)) {
			__free_page(ctx->pages[i]);
			ctx->pages[i] = NULL;
			goto out_of_memory;
		}
		set_page_private(ctx->pages[i], dma_addr);
	}

	for (i = 0; i < AR_BUFFERS; i++)
		pages[i]              = ctx->pages[i];
	for (i = 0; i < AR_WRAPAROUND_PAGES; i++)
		pages[AR_BUFFERS + i] = ctx->pages[i];
	ctx->buffer = vmap(pages, ARRAY_SIZE(pages), VM_MAP, PAGE_KERNEL);
	if (!ctx->buffer)
		goto out_of_memory;

	ctx->descriptors     = ohci->misc_buffer     + descriptors_offset;
	ctx->descriptors_bus = ohci->misc_buffer_bus + descriptors_offset;

	for (i = 0; i < AR_BUFFERS; i++) {
		d = &ctx->descriptors[i];
		d->req_count      = cpu_to_le16(PAGE_SIZE);
		d->control        = cpu_to_le16(DESCRIPTOR_INPUT_MORE |
						DESCRIPTOR_STATUS |
						DESCRIPTOR_BRANCH_ALWAYS);
		d->data_address   = cpu_to_le32(ar_buffer_bus(ctx, i));
		d->branch_address = cpu_to_le32(ctx->descriptors_bus +
			ar_next_buffer_index(i) * sizeof(struct descriptor));
	}

	return 0;

out_of_memory:
	ar_context_release(ctx);

	return -ENOMEM;
}