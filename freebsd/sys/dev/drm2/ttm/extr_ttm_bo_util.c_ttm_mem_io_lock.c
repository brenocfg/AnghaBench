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
struct ttm_mem_type_manager {int /*<<< orphan*/  io_reserve_mutex; int /*<<< orphan*/  io_reserve_fastpath; } ;

/* Variables and functions */
 int EINTR ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sx_xlock_sig (int /*<<< orphan*/ *) ; 

int ttm_mem_io_lock(struct ttm_mem_type_manager *man, bool interruptible)
{
	if (likely(man->io_reserve_fastpath))
		return 0;

	if (interruptible) {
		if (sx_xlock_sig(&man->io_reserve_mutex))
			return (-EINTR);
		else
			return (0);
	}

	sx_xlock(&man->io_reserve_mutex);
	return 0;
}