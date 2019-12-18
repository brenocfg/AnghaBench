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
typedef  scalar_t__ uint8_t ;
struct TYPE_5__ {scalar_t__ stream_id; int flags; int length; scalar_t__* payload; } ;
typedef  TYPE_1__ h2o_http2_frame_t ;
struct TYPE_6__ {scalar_t__* data; scalar_t__ length; } ;
typedef  TYPE_2__ h2o_http2_data_payload_t ;

/* Variables and functions */
 int H2O_HTTP2_ERROR_PROTOCOL ; 
 int H2O_HTTP2_FRAME_FLAG_PADDED ; 

int h2o_http2_decode_data_payload(h2o_http2_data_payload_t *payload, const h2o_http2_frame_t *frame, const char **err_desc)
{
    if (frame->stream_id == 0) {
        *err_desc = "invalid stream id in DATA frame";
        return H2O_HTTP2_ERROR_PROTOCOL;
    }

    if ((frame->flags & H2O_HTTP2_FRAME_FLAG_PADDED) != 0) {
        uint8_t padding_length;
        if (frame->length < 1) {
            *err_desc = "invalid DATA frame";
            return H2O_HTTP2_ERROR_PROTOCOL;
        }
        padding_length = frame->payload[0];
        if (frame->length < 1 + padding_length) {
            *err_desc = "invalid DATA frame";
            return H2O_HTTP2_ERROR_PROTOCOL;
        }
        payload->data = frame->payload + 1;
        payload->length = frame->length - (1 + padding_length);
    } else {
        payload->data = frame->payload;
        payload->length = frame->length;
    }
    return 0;
}