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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 scalar_t__ arc_dnlc_evicts_arg ; 
 int /*<<< orphan*/  arc_dnlc_evicts_cv ; 
 int /*<<< orphan*/  arc_dnlc_evicts_lock ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
dnlc_reduce_cache(void *arg)
{
	u_int percent;

	percent = (u_int)(uintptr_t)arg;
	mutex_enter(&arc_dnlc_evicts_lock);
	if (arc_dnlc_evicts_arg == 0) {
		arc_dnlc_evicts_arg = percent;
		cv_broadcast(&arc_dnlc_evicts_cv);
	}
	mutex_exit(&arc_dnlc_evicts_lock);
}