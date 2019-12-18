#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_http3_server_stream_t {scalar_t__ state; int /*<<< orphan*/  link; TYPE_2__* quic; } ;
struct TYPE_4__ {struct st_h2o_http3_server_stream_t* data; } ;
typedef  TYPE_1__ quicly_stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  sendstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_HTTP3_ERROR_REQUEST_REJECTED ; 
 int /*<<< orphan*/  H2O_HTTP3_SERVER_STREAM_STATE_CLOSE_WAIT ; 
 scalar_t__ H2O_HTTP3_SERVER_STREAM_STATE_RECV_HEADERS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ h2o_linklist_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_linklist_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_reset_stream (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_sendstate_transfer_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_state (struct st_h2o_http3_server_stream_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int on_receive_reset(quicly_stream_t *qs, int err)
{
    struct st_h2o_http3_server_stream_t *stream = qs->data;

    /* if we were still receiving the request, discard! */
    if (stream->state == H2O_HTTP3_SERVER_STREAM_STATE_RECV_HEADERS) {
        assert(!quicly_sendstate_transfer_complete(&stream->quic->sendstate));
        quicly_reset_stream(stream->quic, H2O_HTTP3_ERROR_REQUEST_REJECTED);
        if (h2o_linklist_is_linked(&stream->link))
            h2o_linklist_unlink(&stream->link);
        set_state(stream, H2O_HTTP3_SERVER_STREAM_STATE_CLOSE_WAIT);
    }

    return 0;
}