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
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_trim_enabled ; 

void
trim_thread_destroy(spa_t *spa)
{

	if (!zfs_trim_enabled)
		return;
	if (spa->spa_trim_thread == NULL)
		return;

	mutex_enter(&spa->spa_trim_lock);
	/* Setting spa_trim_thread to NULL tells the thread to stop. */
	spa->spa_trim_thread = NULL;
	cv_signal(&spa->spa_trim_cv);
	/* The thread will set it back to != NULL on exit. */
	while (spa->spa_trim_thread == NULL)
		cv_wait(&spa->spa_trim_cv, &spa->spa_trim_lock);
	spa->spa_trim_thread = NULL;
	mutex_exit(&spa->spa_trim_lock);

	cv_destroy(&spa->spa_trim_cv);
	mutex_destroy(&spa->spa_trim_lock);
}