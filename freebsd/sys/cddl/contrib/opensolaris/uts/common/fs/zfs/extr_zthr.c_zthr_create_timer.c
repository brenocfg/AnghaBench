#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  zthr_state_lock; int /*<<< orphan*/  zthr_thread; int /*<<< orphan*/  zthr_wait_time; void* zthr_arg; int /*<<< orphan*/ * zthr_func; int /*<<< orphan*/ * zthr_checkfunc; int /*<<< orphan*/  zthr_cv; int /*<<< orphan*/  zthr_request_lock; } ;
typedef  TYPE_1__ zthr_t ;
typedef  int /*<<< orphan*/  zthr_func_t ;
typedef  int /*<<< orphan*/  zthr_checkfunc_t ;
typedef  int /*<<< orphan*/  hrtime_t ;

/* Variables and functions */
 int /*<<< orphan*/  CV_DEFAULT ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  TS_RUN ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minclsyspri ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p0 ; 
 int /*<<< orphan*/  thread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zthr_procedure ; 

zthr_t *
zthr_create_timer(zthr_checkfunc_t *checkfunc, zthr_func_t *func,
    void *arg, hrtime_t max_sleep)
{
	zthr_t *t = kmem_zalloc(sizeof (*t), KM_SLEEP);
	mutex_init(&t->zthr_state_lock, NULL, MUTEX_DEFAULT, NULL);
	mutex_init(&t->zthr_request_lock, NULL, MUTEX_DEFAULT, NULL);
	cv_init(&t->zthr_cv, NULL, CV_DEFAULT, NULL);

	mutex_enter(&t->zthr_state_lock);
	t->zthr_checkfunc = checkfunc;
	t->zthr_func = func;
	t->zthr_arg = arg;
	t->zthr_wait_time = max_sleep;

	t->zthr_thread = thread_create(NULL, 0, zthr_procedure, t,
	    0, &p0, TS_RUN, minclsyspri);
	mutex_exit(&t->zthr_state_lock);

	return (t);
}