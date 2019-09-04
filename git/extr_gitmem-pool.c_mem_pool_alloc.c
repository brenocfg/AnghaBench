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
typedef  int /*<<< orphan*/  uintmax_t ;
struct mp_block {size_t end; size_t next_free; } ;
struct mem_pool {int block_alloc; struct mp_block* mp_block; } ;

/* Variables and functions */
 void* mem_pool_alloc_block (struct mem_pool*,size_t,struct mp_block*) ; 

void *mem_pool_alloc(struct mem_pool *mem_pool, size_t len)
{
	struct mp_block *p = NULL;
	void *r;

	/* round up to a 'uintmax_t' alignment */
	if (len & (sizeof(uintmax_t) - 1))
		len += sizeof(uintmax_t) - (len & (sizeof(uintmax_t) - 1));

	if (mem_pool->mp_block &&
	    mem_pool->mp_block->end - mem_pool->mp_block->next_free >= len)
		p = mem_pool->mp_block;

	if (!p) {
		if (len >= (mem_pool->block_alloc / 2))
			return mem_pool_alloc_block(mem_pool, len, mem_pool->mp_block);

		p = mem_pool_alloc_block(mem_pool, mem_pool->block_alloc, NULL);
	}

	r = p->next_free;
	p->next_free += len;
	return r;
}