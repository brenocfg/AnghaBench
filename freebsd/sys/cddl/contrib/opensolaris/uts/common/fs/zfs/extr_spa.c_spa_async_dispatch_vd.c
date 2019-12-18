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
struct TYPE_4__ {int spa_async_tasks; int /*<<< orphan*/  spa_async_lock; int /*<<< orphan*/ * spa_async_thread_vd; int /*<<< orphan*/  spa_async_suspended; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int SPA_ASYNC_REMOVE ; 
 int /*<<< orphan*/  TS_RUN ; 
 int /*<<< orphan*/  maxclsyspri ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p0 ; 
 int /*<<< orphan*/ * rootdir ; 
 int /*<<< orphan*/  spa_async_thread_vd ; 
 int /*<<< orphan*/ * thread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spa_async_dispatch_vd(spa_t *spa)
{
	mutex_enter(&spa->spa_async_lock);
	if ((spa->spa_async_tasks & SPA_ASYNC_REMOVE) != 0 &&
	    !spa->spa_async_suspended &&
	    spa->spa_async_thread_vd == NULL &&
	    rootdir != NULL)
		spa->spa_async_thread_vd = thread_create(NULL, 0,
		    spa_async_thread_vd, spa, 0, &p0, TS_RUN, maxclsyspri);
	mutex_exit(&spa->spa_async_lock);
}