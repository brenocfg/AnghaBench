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
struct mp_block {scalar_t__ end; scalar_t__ space; struct mp_block* next_block; } ;
struct mem_pool {struct mp_block* mp_block; } ;

/* Variables and functions */

int mem_pool_contains(struct mem_pool *mem_pool, void *mem)
{
	struct mp_block *p;

	/* Check if memory is allocated in a block */
	for (p = mem_pool->mp_block; p; p = p->next_block)
		if ((mem >= ((void *)p->space)) &&
		    (mem < ((void *)p->end)))
			return 1;

	return 0;
}