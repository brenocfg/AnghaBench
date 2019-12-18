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
struct TYPE_3__ {int /*<<< orphan*/  spa_trim_lock; int /*<<< orphan*/  spa_trim_cv; int /*<<< orphan*/ * spa_trim_thread; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_trim_enabled ; 

void
trim_thread_wakeup(spa_t *spa)
{

	if (!zfs_trim_enabled)
		return;
	if (spa->spa_trim_thread == NULL)
		return;

	mutex_enter(&spa->spa_trim_lock);
	cv_signal(&spa->spa_trim_cv);
	mutex_exit(&spa->spa_trim_lock);
}