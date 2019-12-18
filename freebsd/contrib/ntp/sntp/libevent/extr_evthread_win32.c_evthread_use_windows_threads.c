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
 int /*<<< orphan*/  evthread_set_condition_callbacks (struct evthread_condition_callbacks*) ; 
 int /*<<< orphan*/  evthread_set_id_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evthread_set_lock_callbacks (struct evthread_lock_callbacks*) ; 
 int /*<<< orphan*/  evthread_win32_cond_alloc ; 
 int /*<<< orphan*/  evthread_win32_cond_free ; 
 int /*<<< orphan*/  evthread_win32_cond_signal ; 
 int /*<<< orphan*/  evthread_win32_cond_wait ; 
 int /*<<< orphan*/  evthread_win32_condvar_alloc ; 
 int /*<<< orphan*/  evthread_win32_condvar_free ; 
 scalar_t__ evthread_win32_condvar_init () ; 
 int /*<<< orphan*/  evthread_win32_condvar_signal ; 
 int /*<<< orphan*/  evthread_win32_condvar_wait ; 
 int /*<<< orphan*/  evthread_win32_get_id ; 
 int /*<<< orphan*/  evthread_win32_lock ; 
 int /*<<< orphan*/  evthread_win32_lock_create ; 
 int /*<<< orphan*/  evthread_win32_lock_free ; 
 int /*<<< orphan*/  evthread_win32_unlock ; 

int
evthread_use_windows_threads(void)
{
	struct evthread_lock_callbacks cbs = {
		EVTHREAD_LOCK_API_VERSION,
		EVTHREAD_LOCKTYPE_RECURSIVE,
		evthread_win32_lock_create,
		evthread_win32_lock_free,
		evthread_win32_lock,
		evthread_win32_unlock
	};


	struct evthread_condition_callbacks cond_cbs = {
		EVTHREAD_CONDITION_API_VERSION,
		evthread_win32_cond_alloc,
		evthread_win32_cond_free,
		evthread_win32_cond_signal,
		evthread_win32_cond_wait
	};
#ifdef WIN32_HAVE_CONDITION_VARIABLES
	struct evthread_condition_callbacks condvar_cbs = {
		EVTHREAD_CONDITION_API_VERSION,
		evthread_win32_condvar_alloc,
		evthread_win32_condvar_free,
		evthread_win32_condvar_signal,
		evthread_win32_condvar_wait
	};
#endif

	evthread_set_lock_callbacks(&cbs);
	evthread_set_id_callback(evthread_win32_get_id);
#ifdef WIN32_HAVE_CONDITION_VARIABLES
	if (evthread_win32_condvar_init()) {
		evthread_set_condition_callbacks(&condvar_cbs);
		return 0;
	}
#endif
	evthread_set_condition_callbacks(&cond_cbs);

	return 0;
}