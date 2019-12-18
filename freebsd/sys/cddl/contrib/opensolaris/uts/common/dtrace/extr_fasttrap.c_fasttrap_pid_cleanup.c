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

/* Variables and functions */
 int /*<<< orphan*/  fasttrap_cleanup_cv ; 
 int /*<<< orphan*/  fasttrap_cleanup_mtx ; 
 int fasttrap_cleanup_work ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fasttrap_pid_cleanup(void)
{

	mtx_lock(&fasttrap_cleanup_mtx);
	if (!fasttrap_cleanup_work) {
		fasttrap_cleanup_work = 1;
		wakeup(&fasttrap_cleanup_cv);
	}
	mtx_unlock(&fasttrap_cleanup_mtx);
}