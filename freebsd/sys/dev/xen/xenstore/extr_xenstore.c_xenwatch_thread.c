#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct xs_stored_msg* vec; int /*<<< orphan*/  vec_size; TYPE_4__* handle; } ;
struct TYPE_6__ {TYPE_1__ watch; } ;
struct xs_stored_msg {TYPE_2__ u; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* callback ) (TYPE_4__*,char const**,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  xenwatch_mutex; int /*<<< orphan*/  watch_events_lock; int /*<<< orphan*/  watch_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_XENSTORE ; 
 int PCATCH ; 
 int PWAIT ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct xs_stored_msg* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct xs_stored_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct xs_stored_msg*,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_sleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 TYPE_3__ xs ; 

__attribute__((used)) static void
xenwatch_thread(void *unused)
{
	struct xs_stored_msg *msg;

	for (;;) {

		mtx_lock(&xs.watch_events_lock);
		while (TAILQ_EMPTY(&xs.watch_events))
			mtx_sleep(&xs.watch_events,
			    &xs.watch_events_lock,
			    PWAIT | PCATCH, "waitev", hz/10);

		mtx_unlock(&xs.watch_events_lock);
		sx_xlock(&xs.xenwatch_mutex);

		mtx_lock(&xs.watch_events_lock);
		msg = TAILQ_FIRST(&xs.watch_events);
		if (msg)
			TAILQ_REMOVE(&xs.watch_events, msg, list);
		mtx_unlock(&xs.watch_events_lock);

		if (msg != NULL) {
			/*
			 * XXX There are messages coming in with a NULL
			 * XXX callback.  This deserves further investigation;
			 * XXX the workaround here simply prevents the kernel
			 * XXX from panic'ing on startup.
			 */
			if (msg->u.watch.handle->callback != NULL)
				msg->u.watch.handle->callback(
					msg->u.watch.handle,
					(const char **)msg->u.watch.vec,
					msg->u.watch.vec_size);
			free(msg->u.watch.vec, M_XENSTORE);
			free(msg, M_XENSTORE);
		}

		sx_xunlock(&xs.xenwatch_mutex);
	}
}