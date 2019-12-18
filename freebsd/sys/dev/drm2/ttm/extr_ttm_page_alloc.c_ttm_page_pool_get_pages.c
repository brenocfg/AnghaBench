#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_page_t ;
struct ttm_page_pool {unsigned int npages; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct pglist {int dummy; } ;
typedef  enum ttm_caching_state { ____Placeholder_ttm_caching_state } ttm_caching_state ;
struct TYPE_2__ {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_CONCAT (struct pglist*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct pglist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ plinks ; 
 int /*<<< orphan*/  ttm_page_pool_fill_locked (struct ttm_page_pool*,int,int,unsigned int) ; 

__attribute__((used)) static unsigned ttm_page_pool_get_pages(struct ttm_page_pool *pool,
					struct pglist *pages,
					int ttm_flags,
					enum ttm_caching_state cstate,
					unsigned count)
{
	vm_page_t p;
	unsigned i;

	mtx_lock(&pool->lock);
	ttm_page_pool_fill_locked(pool, ttm_flags, cstate, count);

	if (count >= pool->npages) {
		/* take all pages from the pool */
		TAILQ_CONCAT(pages, &pool->list, plinks.q);
		count -= pool->npages;
		pool->npages = 0;
		goto out;
	}
	for (i = 0; i < count; i++) {
		p = TAILQ_FIRST(&pool->list);
		TAILQ_REMOVE(&pool->list, p, plinks.q);
		TAILQ_INSERT_TAIL(pages, p, plinks.q);
	}
	pool->npages -= count;
	count = 0;
out:
	mtx_unlock(&pool->lock);
	return count;
}