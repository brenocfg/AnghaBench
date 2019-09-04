#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int len; char* base; } ;
struct TYPE_7__ {int last_stream_id; int error_code; TYPE_1__ debug_data; } ;
typedef  TYPE_2__ h2o_http2_goaway_payload_t ;
struct TYPE_8__ {scalar_t__ stream_id; int length; scalar_t__ payload; } ;
typedef  TYPE_3__ h2o_http2_frame_t ;

/* Variables and functions */
 int H2O_HTTP2_ERROR_FRAME_SIZE ; 
 int H2O_HTTP2_ERROR_PROTOCOL ; 
 int h2o_http2_decode32u (scalar_t__) ; 

int h2o_http2_decode_goaway_payload(h2o_http2_goaway_payload_t *payload, const h2o_http2_frame_t *frame, const char **err_desc)
{
    if (frame->stream_id != 0) {
        *err_desc = "invalid stream id in GOAWAY frame";
        return H2O_HTTP2_ERROR_PROTOCOL;
    }
    if (frame->length < 8) {
        *err_desc = "invalid GOAWAY frame";
        return H2O_HTTP2_ERROR_FRAME_SIZE;
    }

    payload->last_stream_id = h2o_http2_decode32u(frame->payload) & 0x7fffffff;
    payload->error_code = h2o_http2_decode32u(frame->payload + 4);
    if ((payload->debug_data.len = frame->length - 8) != 0)
        payload->debug_data.base = (char *)frame->payload + 8;
    else
        payload->debug_data.base = NULL;

    return 0;
}