#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ssize_t ;
struct TYPE_8__ {int /*<<< orphan*/  output_window; } ;
typedef  TYPE_2__ h2o_http2_stream_t ;
struct TYPE_7__ {size_t max_frame_size; } ;
struct TYPE_9__ {TYPE_1__ peer_settings; } ;
typedef  TYPE_3__ h2o_http2_conn_t ;

/* Variables and functions */
 size_t h2o_http2_conn_get_buffer_window (TYPE_3__*) ; 
 size_t h2o_http2_window_get_avail (int /*<<< orphan*/ *) ; 
 size_t sz_min (size_t,size_t) ; 

__attribute__((used)) static size_t calc_max_payload_size(h2o_http2_conn_t *conn, h2o_http2_stream_t *stream)
{
    ssize_t conn_max, stream_max;

    if ((conn_max = h2o_http2_conn_get_buffer_window(conn)) <= 0)
        return 0;
    if ((stream_max = h2o_http2_window_get_avail(&stream->output_window)) <= 0)
        return 0;
    return sz_min(sz_min(conn_max, stream_max), conn->peer_settings.max_frame_size);
}