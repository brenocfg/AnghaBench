#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  control; } ;
struct TYPE_14__ {TYPE_5__ pending_link; } ;
struct TYPE_15__ {scalar_t__ stream_id; TYPE_6__ _send_aux; TYPE_4__* conn; } ;
typedef  TYPE_7__ quicly_stream_t ;
struct TYPE_9__ {int /*<<< orphan*/  prev; } ;
struct TYPE_10__ {TYPE_1__ control; } ;
struct TYPE_11__ {TYPE_2__ streams; } ;
struct TYPE_12__ {TYPE_3__ pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  quicly_linklist_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_linklist_is_linked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sched_stream_control(quicly_stream_t *stream)
{
    assert(stream->stream_id >= 0);

    if (!quicly_linklist_is_linked(&stream->_send_aux.pending_link.control))
        quicly_linklist_insert(stream->conn->pending.streams.control.prev, &stream->_send_aux.pending_link.control);
}