#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t avail; size_t size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ git_pool_page ;
struct TYPE_6__ {TYPE_1__* pages; } ;
typedef  TYPE_2__ git_pool ;

/* Variables and functions */
 void* pool_alloc_page (TYPE_2__*,size_t) ; 

__attribute__((used)) static void *pool_alloc(git_pool *pool, size_t size)
{
	git_pool_page *page = pool->pages;
	void *ptr = NULL;

	if (!page || page->avail < size)
		return pool_alloc_page(pool, size);

	ptr = &page->data[page->size - page->avail];
	page->avail -= size;

	return ptr;
}