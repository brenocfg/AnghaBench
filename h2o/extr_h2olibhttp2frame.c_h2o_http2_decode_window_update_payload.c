#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int window_size_increment; } ;
typedef  TYPE_1__ h2o_http2_window_update_payload_t ;
struct TYPE_6__ {int length; scalar_t__ stream_id; int /*<<< orphan*/  payload; } ;
typedef  TYPE_2__ h2o_http2_frame_t ;

/* Variables and functions */
 int H2O_HTTP2_ERROR_FRAME_SIZE ; 
 int H2O_HTTP2_ERROR_PROTOCOL ; 
 int h2o_http2_decode32u (int /*<<< orphan*/ ) ; 

int h2o_http2_decode_window_update_payload(h2o_http2_window_update_payload_t *payload, const h2o_http2_frame_t *frame,
                                           const char **err_desc, int *err_is_stream_level)
{
    if (frame->length != 4) {
        *err_is_stream_level = 0;
        *err_desc = "invalid WINDOW_UPDATE frame";
        return H2O_HTTP2_ERROR_FRAME_SIZE;
    }

    payload->window_size_increment = h2o_http2_decode32u(frame->payload) & 0x7fffffff;
    if (payload->window_size_increment == 0) {
        *err_is_stream_level = frame->stream_id != 0;
        *err_desc = "invalid WINDOW_UPDATE frame";
        return H2O_HTTP2_ERROR_PROTOCOL;
    }

    return 0;
}