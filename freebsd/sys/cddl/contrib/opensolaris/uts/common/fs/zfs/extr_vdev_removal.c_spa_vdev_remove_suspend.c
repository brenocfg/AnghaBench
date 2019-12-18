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
struct TYPE_4__ {int /*<<< orphan*/  svr_lock; int /*<<< orphan*/  svr_thread_exit; int /*<<< orphan*/  svr_cv; int /*<<< orphan*/ * svr_thread; } ;
typedef  TYPE_1__ spa_vdev_removal_t ;
struct TYPE_5__ {TYPE_1__* spa_vdev_removal; } ;
typedef  TYPE_2__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
spa_vdev_remove_suspend(spa_t *spa)
{
	spa_vdev_removal_t *svr = spa->spa_vdev_removal;

	if (svr == NULL)
		return;

	mutex_enter(&svr->svr_lock);
	svr->svr_thread_exit = B_TRUE;
	while (svr->svr_thread != NULL)
		cv_wait(&svr->svr_cv, &svr->svr_lock);
	svr->svr_thread_exit = B_FALSE;
	mutex_exit(&svr->svr_lock);
}