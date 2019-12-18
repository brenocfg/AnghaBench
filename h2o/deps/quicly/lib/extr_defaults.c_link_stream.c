#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  prev; } ;
struct st_quicly_default_scheduler_state_t {TYPE_4__ blocked; TYPE_4__ active; } ;
struct TYPE_6__ {int /*<<< orphan*/  default_scheduler; } ;
struct TYPE_7__ {TYPE_1__ pending_link; } ;
struct TYPE_8__ {TYPE_2__ _send_aux; int /*<<< orphan*/  sendstate; } ;
typedef  TYPE_3__ quicly_stream_t ;
typedef  TYPE_4__ quicly_linklist_t ;

/* Variables and functions */
 int /*<<< orphan*/  quicly_linklist_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_linklist_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_sendstate_can_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void link_stream(struct st_quicly_default_scheduler_state_t *sched, quicly_stream_t *stream, int conn_is_flow_capped)
{
    if (!quicly_linklist_is_linked(&stream->_send_aux.pending_link.default_scheduler)) {
        quicly_linklist_t *slot = &sched->active;
        if (conn_is_flow_capped && !quicly_sendstate_can_send(&stream->sendstate, NULL))
            slot = &sched->blocked;
        quicly_linklist_insert(slot->prev, &stream->_send_aux.pending_link.default_scheduler);
    }
}