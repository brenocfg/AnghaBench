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
struct mem_pool {int /*<<< orphan*/  block_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_GROWTH_SIZE ; 
 int /*<<< orphan*/  mem_pool_alloc_block (struct mem_pool*,size_t,int /*<<< orphan*/ *) ; 
 struct mem_pool* xcalloc (int,int) ; 

void mem_pool_init(struct mem_pool **mem_pool, size_t initial_size)
{
	struct mem_pool *pool;

	if (*mem_pool)
		return;

	pool = xcalloc(1, sizeof(*pool));

	pool->block_alloc = BLOCK_GROWTH_SIZE;

	if (initial_size > 0)
		mem_pool_alloc_block(pool, initial_size, NULL);

	*mem_pool = pool;
}