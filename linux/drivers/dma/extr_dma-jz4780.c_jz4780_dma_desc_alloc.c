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
struct jz4780_dma_desc {unsigned int count; int type; int /*<<< orphan*/  desc; int /*<<< orphan*/  desc_phys; } ;
struct jz4780_dma_chan {int /*<<< orphan*/  desc_pool; } ;
typedef  enum dma_transaction_type { ____Placeholder_dma_transaction_type } dma_transaction_type ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 unsigned int JZ_DMA_MAX_DESC ; 
 int /*<<< orphan*/  dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct jz4780_dma_desc*) ; 
 struct jz4780_dma_desc* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct jz4780_dma_desc *jz4780_dma_desc_alloc(
	struct jz4780_dma_chan *jzchan, unsigned int count,
	enum dma_transaction_type type)
{
	struct jz4780_dma_desc *desc;

	if (count > JZ_DMA_MAX_DESC)
		return NULL;

	desc = kzalloc(sizeof(*desc), GFP_NOWAIT);
	if (!desc)
		return NULL;

	desc->desc = dma_pool_alloc(jzchan->desc_pool, GFP_NOWAIT,
				    &desc->desc_phys);
	if (!desc->desc) {
		kfree(desc);
		return NULL;
	}

	desc->count = count;
	desc->type = type;
	return desc;
}