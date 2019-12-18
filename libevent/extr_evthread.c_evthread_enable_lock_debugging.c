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
struct evthread_lock_callbacks {int /*<<< orphan*/  wait_condition; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct evthread_condition_callbacks {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVTHREAD_LOCKTYPE_RECURSIVE ; 
 int /*<<< orphan*/  EVTHREAD_LOCK_API_VERSION ; 
 int /*<<< orphan*/  debug_cond_wait ; 
 int /*<<< orphan*/  debug_lock_alloc ; 
 int /*<<< orphan*/  debug_lock_free ; 
 int /*<<< orphan*/  debug_lock_lock ; 
 int /*<<< orphan*/  debug_lock_unlock ; 
 int /*<<< orphan*/  event_global_setup_locks_ (int /*<<< orphan*/ ) ; 
 struct evthread_lock_callbacks evthread_cond_fns_ ; 
 int evthread_lock_debugging_enabled_ ; 
 struct evthread_lock_callbacks evthread_lock_fns_ ; 
 int /*<<< orphan*/  memcpy (struct evthread_lock_callbacks*,struct evthread_lock_callbacks*,int) ; 
 struct evthread_lock_callbacks original_cond_fns_ ; 
 struct evthread_lock_callbacks original_lock_fns_ ; 

void
evthread_enable_lock_debugging(void)
{
	struct evthread_lock_callbacks cbs = {
		EVTHREAD_LOCK_API_VERSION,
		EVTHREAD_LOCKTYPE_RECURSIVE,
		debug_lock_alloc,
		debug_lock_free,
		debug_lock_lock,
		debug_lock_unlock
	};
	if (evthread_lock_debugging_enabled_)
		return;
	memcpy(&original_lock_fns_, &evthread_lock_fns_,
	    sizeof(struct evthread_lock_callbacks));
	memcpy(&evthread_lock_fns_, &cbs,
	    sizeof(struct evthread_lock_callbacks));

	memcpy(&original_cond_fns_, &evthread_cond_fns_,
	    sizeof(struct evthread_condition_callbacks));
	evthread_cond_fns_.wait_condition = debug_cond_wait;
	evthread_lock_debugging_enabled_ = 1;

	/* XXX return value should get checked. */
	event_global_setup_locks_(0);
}