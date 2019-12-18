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
struct evthread_lock_callbacks {int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct evthread_condition_callbacks {int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVTHREAD_CONDITION_API_VERSION ; 
 int /*<<< orphan*/  EVTHREAD_LOCKTYPE_RECURSIVE ; 
 int /*<<< orphan*/  EVTHREAD_LOCK_API_VERSION ; 
 int /*<<< orphan*/  PTHREAD_MUTEX_RECURSIVE ; 
 int /*<<< orphan*/  attr_recursive ; 
 int /*<<< orphan*/  evthread_posix_cond_alloc ; 
 int /*<<< orphan*/  evthread_posix_cond_free ; 
 int /*<<< orphan*/  evthread_posix_cond_signal ; 
 int /*<<< orphan*/  evthread_posix_cond_wait ; 
 int /*<<< orphan*/  evthread_posix_get_id ; 
 int /*<<< orphan*/  evthread_posix_lock ; 
 int /*<<< orphan*/  evthread_posix_lock_alloc ; 
 int /*<<< orphan*/  evthread_posix_lock_free ; 
 int /*<<< orphan*/  evthread_posix_unlock ; 
 int /*<<< orphan*/  evthread_set_condition_callbacks (struct evthread_condition_callbacks*) ; 
 int /*<<< orphan*/  evthread_set_id_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evthread_set_lock_callbacks (struct evthread_lock_callbacks*) ; 
 scalar_t__ pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_settype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
evthread_use_pthreads(void)
{
	struct evthread_lock_callbacks cbs = {
		EVTHREAD_LOCK_API_VERSION,
		EVTHREAD_LOCKTYPE_RECURSIVE,
		evthread_posix_lock_alloc,
		evthread_posix_lock_free,
		evthread_posix_lock,
		evthread_posix_unlock
	};
	struct evthread_condition_callbacks cond_cbs = {
		EVTHREAD_CONDITION_API_VERSION,
		evthread_posix_cond_alloc,
		evthread_posix_cond_free,
		evthread_posix_cond_signal,
		evthread_posix_cond_wait
	};
	/* Set ourselves up to get recursive locks. */
	if (pthread_mutexattr_init(&attr_recursive))
		return -1;
	if (pthread_mutexattr_settype(&attr_recursive, PTHREAD_MUTEX_RECURSIVE))
		return -1;

	evthread_set_lock_callbacks(&cbs);
	evthread_set_condition_callbacks(&cond_cbs);
	evthread_set_id_callback(evthread_posix_get_id);
	return 0;
}