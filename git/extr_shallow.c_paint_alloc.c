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
typedef  void uint32_t ;
struct paint_info {int pool_count; int end; unsigned int free; unsigned int* pools; int /*<<< orphan*/  nr_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,unsigned int) ; 
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 unsigned int POOL_SIZE ; 
 int /*<<< orphan*/  REALLOC_ARRAY (unsigned int*,int) ; 
 unsigned int xmalloc (unsigned int) ; 

__attribute__((used)) static uint32_t *paint_alloc(struct paint_info *info)
{
	unsigned nr = DIV_ROUND_UP(info->nr_bits, 32);
	unsigned size = nr * sizeof(uint32_t);
	void *p;
	if (!info->pool_count || size > info->end - info->free) {
		if (size > POOL_SIZE)
			BUG("pool size too small for %d in paint_alloc()",
			    size);
		info->pool_count++;
		REALLOC_ARRAY(info->pools, info->pool_count);
		info->free = xmalloc(POOL_SIZE);
		info->pools[info->pool_count - 1] = info->free;
		info->end = info->free + POOL_SIZE;
	}
	p = info->free;
	info->free += size;
	return p;
}