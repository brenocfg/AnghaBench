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
struct mp_block {scalar_t__ space; scalar_t__ end; struct mp_block* next_block; struct mp_block* mp_block; } ;
struct mem_pool {scalar_t__ space; scalar_t__ end; struct mem_pool* next_block; struct mem_pool* mp_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct mp_block*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 

void mem_pool_discard(struct mem_pool *mem_pool, int invalidate_memory)
{
	struct mp_block *block, *block_to_free;

	block = mem_pool->mp_block;
	while (block)
	{
		block_to_free = block;
		block = block->next_block;

		if (invalidate_memory)
			memset(block_to_free->space, 0xDD, ((char *)block_to_free->end) - ((char *)block_to_free->space));

		free(block_to_free);
	}

	free(mem_pool);
}