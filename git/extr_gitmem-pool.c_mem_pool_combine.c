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
struct mp_block {struct mp_block* next_block; } ;
struct mem_pool {struct mp_block* mp_block; scalar_t__ pool_alloc; } ;

/* Variables and functions */

void mem_pool_combine(struct mem_pool *dst, struct mem_pool *src)
{
	struct mp_block *p;

	/* Append the blocks from src to dst */
	if (dst->mp_block && src->mp_block) {
		/*
		 * src and dst have blocks, append
		 * blocks from src to dst.
		 */
		p = dst->mp_block;
		while (p->next_block)
			p = p->next_block;

		p->next_block = src->mp_block;
	} else if (src->mp_block) {
		/*
		 * src has blocks, dst is empty.
		 */
		dst->mp_block = src->mp_block;
	} else {
		/* src is empty, nothing to do. */
	}

	dst->pool_alloc += src->pool_alloc;
	src->pool_alloc = 0;
	src->mp_block = NULL;
}