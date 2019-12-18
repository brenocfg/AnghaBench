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
typedef  int /*<<< orphan*/  zthr_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ aggsum_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ arc_adjust () ; 
 int /*<<< orphan*/  arc_adjust_lock ; 
 int arc_adjust_needed ; 
 int /*<<< orphan*/  arc_adjust_waiters_cv ; 
 int /*<<< orphan*/  arc_adjust_zthr ; 
 int /*<<< orphan*/  arc_c ; 
 int /*<<< orphan*/  arc_size ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zthr_iscancelled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arc_adjust_cb(void *arg, zthr_t *zthr)
{
	uint64_t evicted = 0;

	/* Evict from cache */
	evicted = arc_adjust();

	/*
	 * If evicted is zero, we couldn't evict anything
	 * via arc_adjust(). This could be due to hash lock
	 * collisions, but more likely due to the majority of
	 * arc buffers being unevictable. Therefore, even if
	 * arc_size is above arc_c, another pass is unlikely to
	 * be helpful and could potentially cause us to enter an
	 * infinite loop.  Additionally, zthr_iscancelled() is
	 * checked here so that if the arc is shutting down, the
	 * broadcast will wake any remaining arc adjust waiters.
	 */
	mutex_enter(&arc_adjust_lock);
	arc_adjust_needed = !zthr_iscancelled(arc_adjust_zthr) &&
	    evicted > 0 && aggsum_compare(&arc_size, arc_c) > 0;
	if (!arc_adjust_needed) {
		/*
		 * We're either no longer overflowing, or we
		 * can't evict anything more, so we should wake
		 * up any waiters.
		 */
		cv_broadcast(&arc_adjust_waiters_cv);
	}
	mutex_exit(&arc_adjust_lock);
}