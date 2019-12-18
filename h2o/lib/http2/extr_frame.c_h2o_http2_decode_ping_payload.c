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
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ h2o_http2_ping_payload_t ;
struct TYPE_6__ {scalar_t__ stream_id; int length; int /*<<< orphan*/  payload; } ;
typedef  TYPE_2__ h2o_http2_frame_t ;

/* Variables and functions */
 int H2O_HTTP2_ERROR_FRAME_SIZE ; 
 int H2O_HTTP2_ERROR_PROTOCOL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int h2o_http2_decode_ping_payload(h2o_http2_ping_payload_t *payload, const h2o_http2_frame_t *frame, const char **err_desc)
{
    if (frame->stream_id != 0) {
        *err_desc = "invalid PING frame";
        return H2O_HTTP2_ERROR_PROTOCOL;
    }
    if (frame->length != sizeof(payload->data)) {
        *err_desc = "invalid PING frame";
        return H2O_HTTP2_ERROR_FRAME_SIZE;
    }

    memcpy(payload->data, frame->payload, sizeof(payload->data));
    return 0;
}