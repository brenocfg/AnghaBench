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
typedef  union al_udma_desc {int dummy; } al_udma_desc ;
typedef  size_t uint32_t ;
struct al_udma_q {size_t cdesc_size; size_t size; void* cdesc_base_ptr; void* desc_base_ptr; } ;
struct al_udma {struct al_udma_q* udma_q; } ;
typedef  enum al_udma_ring_type { ____Placeholder_al_udma_ring_type } al_udma_ring_type ;

/* Variables and functions */
 int AL_RING_SUBMISSION ; 
 size_t DMA_MAX_Q ; 
 int /*<<< orphan*/  al_dbg (char*,size_t,...) ; 

void al_udma_ring_print(struct al_udma *udma, uint32_t qid,
		enum al_udma_ring_type rtype)
{
	struct al_udma_q *queue;
	uint32_t desc_size;
	void *base_ptr;
	uint32_t i;

	if (!udma)
		return;

	if (qid >= DMA_MAX_Q)
		return;

	queue = &udma->udma_q[qid];
	if (rtype == AL_RING_SUBMISSION) {
		base_ptr = queue->desc_base_ptr;
		desc_size = sizeof(union al_udma_desc);
		if (base_ptr)
			al_dbg("Q[%d] submission ring pointers:\n", qid);
		else {
			al_dbg("Q[%d] submission ring is not allocated\n", qid);
			return;
		}
	} else {
		base_ptr = queue->cdesc_base_ptr;
		desc_size = queue->cdesc_size;
		if (base_ptr)
			al_dbg("Q[%d] completion ring pointers:\n", qid);
		else {
			al_dbg("Q[%d] completion ring is not allocated\n", qid);
			return;
		}
	}

	for (i = 0; i < queue->size; i++) {
		uint32_t *curr_addr = (void*)((uintptr_t)base_ptr + i * desc_size);
		if (desc_size == 16)
			al_dbg("[%04d](%p): %08x %08x %08x %08x\n",
					i,
					curr_addr,
					(uint32_t)*curr_addr,
					(uint32_t)*(curr_addr+1),
					(uint32_t)*(curr_addr+2),
					(uint32_t)*(curr_addr+3));
		else if (desc_size == 8)
			al_dbg("[%04d](%p): %08x %08x\n",
					i,
					curr_addr,
					(uint32_t)*curr_addr,
					(uint32_t)*(curr_addr+1));
		else if (desc_size == 4)
			al_dbg("[%04d](%p): %08x\n",
					i,
					curr_addr,
					(uint32_t)*curr_addr);
		else
			break;
	}
}