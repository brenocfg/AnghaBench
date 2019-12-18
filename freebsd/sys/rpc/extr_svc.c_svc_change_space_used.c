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
struct TYPE_4__ {unsigned long sp_space_high; unsigned long sp_space_used_highest; unsigned long sp_space_low; scalar_t__ sp_space_throttled; int /*<<< orphan*/  sp_space_throttle_count; int /*<<< orphan*/  sp_space_used; } ;
typedef  TYPE_1__ SVCPOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 long atomic_fetchadd_long (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  svc_assign_waiting_sockets (TYPE_1__*) ; 

__attribute__((used)) static void
svc_change_space_used(SVCPOOL *pool, long delta)
{
	unsigned long value;

	value = atomic_fetchadd_long(&pool->sp_space_used, delta) + delta;
	if (delta > 0) {
		if (value >= pool->sp_space_high && !pool->sp_space_throttled) {
			pool->sp_space_throttled = TRUE;
			pool->sp_space_throttle_count++;
		}
		if (value > pool->sp_space_used_highest)
			pool->sp_space_used_highest = value;
	} else {
		if (value < pool->sp_space_low && pool->sp_space_throttled) {
			pool->sp_space_throttled = FALSE;
			svc_assign_waiting_sockets(pool);
		}
	}
}