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
typedef  int /*<<< orphan*/  git_pool ;

/* Variables and functions */
 size_t alloc_size (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (void*,int,size_t const) ; 
 void* pool_alloc (int /*<<< orphan*/ *,size_t const) ; 

void *git_pool_mallocz(git_pool *pool, size_t items)
{
	const size_t size = alloc_size(pool, items);
	void *ptr = pool_alloc(pool, size);
	if (ptr)
		memset(ptr, 0x0, size);
	return ptr;
}