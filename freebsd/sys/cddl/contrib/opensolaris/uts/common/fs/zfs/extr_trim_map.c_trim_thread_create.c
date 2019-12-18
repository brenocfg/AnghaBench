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
struct TYPE_4__ {int /*<<< orphan*/  spa_trim_lock; int /*<<< orphan*/  spa_trim_thread; int /*<<< orphan*/  spa_trim_cv; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  CV_DEFAULT ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  TS_RUN ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  minclsyspri ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p0 ; 
 int /*<<< orphan*/  thread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trim_thread ; 
 int /*<<< orphan*/  zfs_trim_enabled ; 

void
trim_thread_create(spa_t *spa)
{

	if (!zfs_trim_enabled)
		return;

	mutex_init(&spa->spa_trim_lock, NULL, MUTEX_DEFAULT, NULL);
	cv_init(&spa->spa_trim_cv, NULL, CV_DEFAULT, NULL);
	mutex_enter(&spa->spa_trim_lock);
	spa->spa_trim_thread = thread_create(NULL, 0, trim_thread, spa, 0, &p0,
	    TS_RUN, minclsyspri);
	mutex_exit(&spa->spa_trim_lock);
}