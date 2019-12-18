#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pool_hdr_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; scalar_t__ use_lock; int /*<<< orphan*/  freelist; } ;
typedef  TYPE_1__ ocs_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

void
ocs_pool_put(ocs_pool_t *pool, void *item)
{
	pool_hdr_t *h;

	if (pool->use_lock) {
		ocs_lock(&pool->lock);
	}

	/* Fetch the address of the array item, which is the item address negatively offset
	 * by size of pool_hdr_t (note the index of [-1]
	 */
	h = &((pool_hdr_t*)item)[-1];

	ocs_list_add_tail(&pool->freelist, h);

	if (pool->use_lock) {
		ocs_unlock(&pool->lock);
	}

}