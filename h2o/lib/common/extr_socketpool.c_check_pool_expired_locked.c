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
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/ * loop; } ;
struct TYPE_6__ {TYPE_1__ _interval_cb; } ;
typedef  TYPE_2__ h2o_socketpool_t ;
typedef  int /*<<< orphan*/  h2o_loop_t ;

/* Variables and functions */
 scalar_t__ CHECK_EXPIRATION_MIN_INTERVAL ; 
 scalar_t__ UINT64_MAX ; 
 scalar_t__ destroy_expired_locked (TYPE_2__*) ; 
 int /*<<< orphan*/  h2o_timer_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_pool_expired_locked(h2o_socketpool_t *pool, h2o_loop_t *this_loop)
{
    uint64_t next_expired = destroy_expired_locked(pool);
    if (next_expired != UINT64_MAX) {
        if (this_loop == pool->_interval_cb.loop && !h2o_timer_is_linked(&pool->_interval_cb.timeout)) {
            if (next_expired < CHECK_EXPIRATION_MIN_INTERVAL)
                next_expired = CHECK_EXPIRATION_MIN_INTERVAL;
            h2o_timer_link(pool->_interval_cb.loop, next_expired, &pool->_interval_cb.timeout);
        }
    }
}