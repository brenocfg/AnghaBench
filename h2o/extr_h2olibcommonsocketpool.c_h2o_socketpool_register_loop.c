#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/ * loop; } ;
struct TYPE_5__ {TYPE_1__ _interval_cb; } ;
typedef  TYPE_2__ h2o_socketpool_t ;
typedef  int /*<<< orphan*/  h2o_loop_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_EXPIRATION_MIN_INTERVAL ; 
 int /*<<< orphan*/  h2o_timer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_timeout ; 

void h2o_socketpool_register_loop(h2o_socketpool_t *pool, h2o_loop_t *loop)
{
    if (pool->_interval_cb.loop != NULL)
        return;

    pool->_interval_cb.loop = loop;
    h2o_timer_init(&pool->_interval_cb.timeout, on_timeout);
    h2o_timer_link(loop, CHECK_EXPIRATION_MIN_INTERVAL, &pool->_interval_cb.timeout);
}