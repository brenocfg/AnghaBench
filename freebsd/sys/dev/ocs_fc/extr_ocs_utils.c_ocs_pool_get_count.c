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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; scalar_t__ use_lock; int /*<<< orphan*/  a; } ;
typedef  TYPE_1__ ocs_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_array_get_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

uint32_t
ocs_pool_get_count(ocs_pool_t *pool)
{
	uint32_t count;
	if (pool->use_lock) {
		ocs_lock(&pool->lock);
	}
	count = ocs_array_get_count(pool->a);
	if (pool->use_lock) {
		ocs_unlock(&pool->lock);
	}
	return count;
}