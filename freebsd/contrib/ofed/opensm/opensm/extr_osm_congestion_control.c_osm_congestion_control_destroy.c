#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  osm_madw_t ;
struct TYPE_3__ {int /*<<< orphan*/  log; int /*<<< orphan*/  sig_mads_on_wire_continue; int /*<<< orphan*/  outstanding_mads_done_event; int /*<<< orphan*/  cc_poller_wakeup; int /*<<< orphan*/  mad_queue_lock; int /*<<< orphan*/  mad_pool; int /*<<< orphan*/  mad_queue; int /*<<< orphan*/  cc_poller; int /*<<< orphan*/  thread_state; } ;
typedef  TYPE_1__ osm_congestion_control_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_THREAD_STATE_EXIT ; 
 int /*<<< orphan*/  cl_event_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_event_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_is_qlist_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qlist_remove_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_spinlock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_spinlock_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_spinlock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_thread_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osm_mad_pool_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void osm_congestion_control_destroy(osm_congestion_control_t * p_cc)
{
	osm_madw_t *p_madw;

	OSM_LOG_ENTER(p_cc->log);

	p_cc->thread_state = OSM_THREAD_STATE_EXIT;

	cl_event_signal(&p_cc->sig_mads_on_wire_continue);
	cl_event_signal(&p_cc->cc_poller_wakeup);

	cl_thread_destroy(&p_cc->cc_poller);

	cl_spinlock_acquire(&p_cc->mad_queue_lock);

	while (!cl_is_qlist_empty(&p_cc->mad_queue)) {
		p_madw = (osm_madw_t *) cl_qlist_remove_head(&p_cc->mad_queue);
		osm_mad_pool_put(p_cc->mad_pool, p_madw);
	}

	cl_spinlock_release(&p_cc->mad_queue_lock);

	cl_spinlock_destroy(&p_cc->mad_queue_lock);

	cl_event_destroy(&p_cc->cc_poller_wakeup);
	cl_event_destroy(&p_cc->outstanding_mads_done_event);
	cl_event_destroy(&p_cc->sig_mads_on_wire_continue);

	OSM_LOG_EXIT(p_cc->log);
}