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
struct ttm_page_pool {int fill_lock; int ttm_page_alloc_flags; char* name; scalar_t__ nfrees; scalar_t__ npages; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ttm_page_pool_init_locked(struct ttm_page_pool *pool, int flags,
				      char *name)
{
	mtx_init(&pool->lock, "ttmpool", NULL, MTX_DEF);
	pool->fill_lock = false;
	TAILQ_INIT(&pool->list);
	pool->npages = pool->nfrees = 0;
	pool->ttm_page_alloc_flags = flags;
	pool->name = name;
}