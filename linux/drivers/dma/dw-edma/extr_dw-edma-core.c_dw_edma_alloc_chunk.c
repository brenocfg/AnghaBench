#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dw_edma_desc {int chunks_alloc; struct dw_edma_chunk* chunk; struct dw_edma_chan* chan; } ;
struct TYPE_5__ {scalar_t__ vaddr; scalar_t__ paddr; } ;
struct dw_edma_chunk {int cb; int /*<<< orphan*/ * burst; int /*<<< orphan*/  list; TYPE_2__ ll_region; struct dw_edma_chan* chan; } ;
struct dw_edma_chan {scalar_t__ ll_off; TYPE_1__* chip; } ;
struct TYPE_6__ {scalar_t__ vaddr; scalar_t__ paddr; } ;
struct dw_edma {TYPE_3__ ll_region; } ;
struct TYPE_4__ {struct dw_edma* dw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dw_edma_alloc_burst (struct dw_edma_chunk*) ; 
 int /*<<< orphan*/  kfree (struct dw_edma_chunk*) ; 
 struct dw_edma_chunk* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct dw_edma_chunk *dw_edma_alloc_chunk(struct dw_edma_desc *desc)
{
	struct dw_edma_chan *chan = desc->chan;
	struct dw_edma *dw = chan->chip->dw;
	struct dw_edma_chunk *chunk;

	chunk = kzalloc(sizeof(*chunk), GFP_NOWAIT);
	if (unlikely(!chunk))
		return NULL;

	INIT_LIST_HEAD(&chunk->list);
	chunk->chan = chan;
	/* Toggling change bit (CB) in each chunk, this is a mechanism to
	 * inform the eDMA HW block that this is a new linked list ready
	 * to be consumed.
	 *  - Odd chunks originate CB equal to 0
	 *  - Even chunks originate CB equal to 1
	 */
	chunk->cb = !(desc->chunks_alloc % 2);
	chunk->ll_region.paddr = dw->ll_region.paddr + chan->ll_off;
	chunk->ll_region.vaddr = dw->ll_region.vaddr + chan->ll_off;

	if (desc->chunk) {
		/* Create and add new element into the linked list */
		desc->chunks_alloc++;
		list_add_tail(&chunk->list, &desc->chunk->list);
		if (!dw_edma_alloc_burst(chunk)) {
			kfree(chunk);
			return NULL;
		}
	} else {
		/* List head */
		chunk->burst = NULL;
		desc->chunks_alloc = 0;
		desc->chunk = chunk;
	}

	return chunk;
}