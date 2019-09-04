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
struct TYPE_4__ {scalar_t__ bytes_unnotified; int /*<<< orphan*/  window; } ;
struct TYPE_5__ {TYPE_1__ input_window; int /*<<< orphan*/  stream_id; } ;
typedef  TYPE_2__ h2o_http2_stream_t ;
typedef  int /*<<< orphan*/  h2o_http2_conn_t ;

/* Variables and functions */
 scalar_t__ h2o_http2_window_get_avail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_window_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

void update_stream_input_window(h2o_http2_conn_t *conn, h2o_http2_stream_t *stream, size_t delta)
{
    stream->input_window.bytes_unnotified += delta;
    if (stream->input_window.bytes_unnotified >= h2o_http2_window_get_avail(&stream->input_window.window)) {
        send_window_update(conn, stream->stream_id, &stream->input_window.window, stream->input_window.bytes_unnotified);
        stream->input_window.bytes_unnotified = 0;
    }
}