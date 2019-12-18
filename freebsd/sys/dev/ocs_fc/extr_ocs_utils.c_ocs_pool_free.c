#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  os; int /*<<< orphan*/  lock; scalar_t__ use_lock; int /*<<< orphan*/ * a; } ;
typedef  TYPE_1__ ocs_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_array_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ocs_lock_free (int /*<<< orphan*/ *) ; 

void
ocs_pool_free(ocs_pool_t *pool)
{
	if (pool != NULL) {
		if (pool->a != NULL) {
			ocs_array_free(pool->a);
		}
		if (pool->use_lock) {
			ocs_lock_free(&pool->lock);
		}
		ocs_free(pool->os, pool, sizeof(*pool));
	}
}