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
struct user_evtchn {int enabled; int /*<<< orphan*/  handle; struct per_user_data* user; int /*<<< orphan*/  port; } ;
struct per_user_data {int /*<<< orphan*/  bind_mutex; int /*<<< orphan*/  evtchns; } ;

/* Variables and functions */
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  M_EVTCHN ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct user_evtchn*) ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct user_evtchn*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evtchn_dev ; 
 int /*<<< orphan*/  evtchn_filter ; 
 int /*<<< orphan*/  evtchn_interrupt ; 
 int /*<<< orphan*/  evtchn_tree ; 
 int /*<<< orphan*/  free (struct user_evtchn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int xen_intr_add_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct user_evtchn*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_intr_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_intr_unbind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
evtchn_bind_user_port(struct per_user_data *u, struct user_evtchn *evtchn)
{
	int error;

	evtchn->port = xen_intr_port(evtchn->handle);
	evtchn->user = u;
	evtchn->enabled = true;
	mtx_lock(&u->bind_mutex);
	RB_INSERT(evtchn_tree, &u->evtchns, evtchn);
	mtx_unlock(&u->bind_mutex);
	error = xen_intr_add_handler(device_get_nameunit(evtchn_dev),
	    evtchn_filter, evtchn_interrupt, evtchn,
	    INTR_TYPE_MISC | INTR_MPSAFE, evtchn->handle);
	if (error != 0) {
		xen_intr_unbind(&evtchn->handle);
		mtx_lock(&u->bind_mutex);
		RB_REMOVE(evtchn_tree, &u->evtchns, evtchn);
		mtx_unlock(&u->bind_mutex);
		free(evtchn, M_EVTCHN);
	}
	return (error);
}