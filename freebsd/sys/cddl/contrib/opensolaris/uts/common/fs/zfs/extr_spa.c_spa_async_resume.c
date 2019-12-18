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
typedef  int /*<<< orphan*/  zthr_t ;
struct TYPE_4__ {scalar_t__ spa_async_suspended; int /*<<< orphan*/ * spa_checkpoint_discard_zthr; int /*<<< orphan*/ * spa_condense_zthr; int /*<<< orphan*/  spa_async_lock; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_restart_removal (TYPE_1__*) ; 
 int /*<<< orphan*/  zthr_resume (int /*<<< orphan*/ *) ; 

void
spa_async_resume(spa_t *spa)
{
	mutex_enter(&spa->spa_async_lock);
	ASSERT(spa->spa_async_suspended != 0);
	spa->spa_async_suspended--;
	mutex_exit(&spa->spa_async_lock);
	spa_restart_removal(spa);

	zthr_t *condense_thread = spa->spa_condense_zthr;
	if (condense_thread != NULL)
		zthr_resume(condense_thread);

	zthr_t *discard_thread = spa->spa_checkpoint_discard_zthr;
	if (discard_thread != NULL)
		zthr_resume(discard_thread);
}