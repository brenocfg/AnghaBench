#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_8__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_9__ {int /*<<< orphan*/  spa_root_vdev; int /*<<< orphan*/  spa_trim_lock; int /*<<< orphan*/  spa_trim_cv; TYPE_8__* spa_trim_thread; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_10__ {int /*<<< orphan*/  td_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_STATE ; 
 int /*<<< orphan*/  ZIO_FLAG_CANFAIL ; 
 TYPE_8__* curthread ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int hz ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* spa_name (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_exit () ; 
 int /*<<< orphan*/  trim_map_commit (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trim_map_commit_done (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int trim_max_interval ; 
 int /*<<< orphan*/ * zio_root (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
trim_thread(void *arg)
{
	spa_t *spa = arg;
	zio_t *zio;

#ifdef _KERNEL
	(void) snprintf(curthread->td_name, sizeof(curthread->td_name),
	    "trim %s", spa_name(spa));
#endif

	for (;;) {
		mutex_enter(&spa->spa_trim_lock);
		if (spa->spa_trim_thread == NULL) {
			spa->spa_trim_thread = curthread;
			cv_signal(&spa->spa_trim_cv);
			mutex_exit(&spa->spa_trim_lock);
			thread_exit();
		}

		(void) cv_timedwait(&spa->spa_trim_cv, &spa->spa_trim_lock,
		    hz * trim_max_interval);
		mutex_exit(&spa->spa_trim_lock);

		zio = zio_root(spa, NULL, NULL, ZIO_FLAG_CANFAIL);

		spa_config_enter(spa, SCL_STATE, FTAG, RW_READER);
		trim_map_commit(spa, zio, spa->spa_root_vdev);
		(void) zio_wait(zio);
		trim_map_commit_done(spa, spa->spa_root_vdev);
		spa_config_exit(spa, SCL_STATE, FTAG);
	}
}