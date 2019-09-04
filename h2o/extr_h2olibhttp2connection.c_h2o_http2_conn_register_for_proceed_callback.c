#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ state; int /*<<< orphan*/  _link; int /*<<< orphan*/  _scheduler; int /*<<< orphan*/  output_window; } ;
typedef  TYPE_2__ h2o_http2_stream_t ;
struct TYPE_8__ {int /*<<< orphan*/  streams_to_proceed; } ;
struct TYPE_10__ {TYPE_1__ _write; } ;
typedef  TYPE_3__ h2o_http2_conn_t ;

/* Variables and functions */
 scalar_t__ H2O_HTTP2_STREAM_STATE_SEND_BODY_IS_FINAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  h2o_http2_conn_request_write (TYPE_3__*) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_activate (int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_http2_stream_has_pending_data (TYPE_2__*) ; 
 scalar_t__ h2o_http2_window_get_avail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_linklist_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_linklist_is_linked (int /*<<< orphan*/ *) ; 

void h2o_http2_conn_register_for_proceed_callback(h2o_http2_conn_t *conn, h2o_http2_stream_t *stream)
{
    h2o_http2_conn_request_write(conn);

    if (h2o_http2_stream_has_pending_data(stream) || stream->state >= H2O_HTTP2_STREAM_STATE_SEND_BODY_IS_FINAL) {
        if (h2o_http2_window_get_avail(&stream->output_window) > 0) {
            assert(!h2o_linklist_is_linked(&stream->_link));
            h2o_http2_scheduler_activate(&stream->_scheduler);
        }
    } else {
        h2o_linklist_insert(&conn->_write.streams_to_proceed, &stream->_link);
    }
}