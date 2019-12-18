#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_http2_priority_t ;
struct TYPE_3__ {scalar_t__ stream_id; int length; int /*<<< orphan*/  payload; } ;
typedef  TYPE_1__ h2o_http2_frame_t ;

/* Variables and functions */
 int H2O_HTTP2_ERROR_FRAME_SIZE ; 
 int H2O_HTTP2_ERROR_PROTOCOL ; 
 int /*<<< orphan*/  decode_priority (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int h2o_http2_decode_priority_payload(h2o_http2_priority_t *payload, const h2o_http2_frame_t *frame, const char **err_desc)
{
    if (frame->stream_id == 0) {
        *err_desc = "invalid stream id in PRIORITY frame";
        return H2O_HTTP2_ERROR_PROTOCOL;
    }
    if (frame->length != 5) {
        *err_desc = "invalid PRIORITY frame";
        return H2O_HTTP2_ERROR_FRAME_SIZE;
    }

    decode_priority(payload, frame->payload);
    return 0;
}