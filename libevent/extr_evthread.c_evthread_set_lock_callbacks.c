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
struct evthread_lock_callbacks {scalar_t__ alloc; scalar_t__ lock_api_version; scalar_t__ supported_locktypes; scalar_t__ free; scalar_t__ lock; scalar_t__ unlock; } ;
typedef  int /*<<< orphan*/  evthread_lock_fns_ ;

/* Variables and functions */
 scalar_t__ event_debug_created_threadable_ctx_ ; 
 scalar_t__ event_debug_mode_on_ ; 
 int /*<<< orphan*/  event_errx (int,char*) ; 
 int event_global_setup_locks_ (int) ; 
 int /*<<< orphan*/  event_warnx (char*) ; 
 struct evthread_lock_callbacks* evthread_get_lock_callbacks () ; 
 int /*<<< orphan*/  memcpy (struct evthread_lock_callbacks*,struct evthread_lock_callbacks const*,int) ; 
 int /*<<< orphan*/  memset (struct evthread_lock_callbacks*,int /*<<< orphan*/ ,int) ; 

int
evthread_set_lock_callbacks(const struct evthread_lock_callbacks *cbs)
{
	struct evthread_lock_callbacks *target = evthread_get_lock_callbacks();

#ifndef EVENT__DISABLE_DEBUG_MODE
	if (event_debug_mode_on_) {
		if (event_debug_created_threadable_ctx_) {
		    event_errx(1, "evthread initialization must be called BEFORE anything else!");
		}
	}
#endif

	if (!cbs) {
		if (target->alloc)
			event_warnx("Trying to disable lock functions after "
			    "they have been set up will probaby not work.");
		memset(target, 0, sizeof(evthread_lock_fns_));
		return 0;
	}
	if (target->alloc) {
		/* Uh oh; we already had locking callbacks set up.*/
		if (target->lock_api_version == cbs->lock_api_version &&
			target->supported_locktypes == cbs->supported_locktypes &&
			target->alloc == cbs->alloc &&
			target->free == cbs->free &&
			target->lock == cbs->lock &&
			target->unlock == cbs->unlock) {
			/* no change -- allow this. */
			return 0;
		}
		event_warnx("Can't change lock callbacks once they have been "
		    "initialized.");
		return -1;
	}
	if (cbs->alloc && cbs->free && cbs->lock && cbs->unlock) {
		memcpy(target, cbs, sizeof(evthread_lock_fns_));
		return event_global_setup_locks_(1);
	} else {
		return -1;
	}
}