#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  default_scheduler; int /*<<< orphan*/  control; } ;
struct TYPE_6__ {TYPE_1__ pending_link; int /*<<< orphan*/  max_stream_data_sender; } ;
struct TYPE_7__ {TYPE_2__ _send_aux; int /*<<< orphan*/  recvstate; int /*<<< orphan*/  sendstate; } ;
typedef  TYPE_3__ quicly_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  quicly_linklist_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_maxsender_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_recvstate_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_sendstate_dispose (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dispose_stream_properties(quicly_stream_t *stream)
{
    quicly_sendstate_dispose(&stream->sendstate);
    quicly_recvstate_dispose(&stream->recvstate);
    quicly_maxsender_dispose(&stream->_send_aux.max_stream_data_sender);
    quicly_linklist_unlink(&stream->_send_aux.pending_link.control);
    quicly_linklist_unlink(&stream->_send_aux.pending_link.default_scheduler);
}