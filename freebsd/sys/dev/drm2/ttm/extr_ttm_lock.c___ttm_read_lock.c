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
struct ttm_lock {scalar_t__ rw; scalar_t__ flags; int /*<<< orphan*/  signal; int /*<<< orphan*/  kill_takers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttm_lock_send_sig (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __ttm_read_lock(struct ttm_lock *lock)
{
	bool locked = false;

	if (unlikely(lock->kill_takers)) {
		ttm_lock_send_sig(lock->signal);
		return false;
	}
	if (lock->rw >= 0 && lock->flags == 0) {
		++lock->rw;
		locked = true;
	}
	return locked;
}