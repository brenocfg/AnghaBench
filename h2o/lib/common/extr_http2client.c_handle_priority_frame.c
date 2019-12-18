#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_http2client_conn_t {int dummy; } ;
struct TYPE_6__ {scalar_t__ dependency; } ;
typedef  TYPE_1__ h2o_http2_priority_t ;
struct TYPE_7__ {scalar_t__ stream_id; } ;
typedef  TYPE_2__ h2o_http2_frame_t ;

/* Variables and functions */
 int H2O_HTTP2_ERROR_PROTOCOL ; 
 int h2o_http2_decode_priority_payload (TYPE_1__*,TYPE_2__*,char const**) ; 

__attribute__((used)) static int handle_priority_frame(struct st_h2o_http2client_conn_t *conn, h2o_http2_frame_t *frame, const char **err_desc)
{
    h2o_http2_priority_t payload;
    int ret;

    if ((ret = h2o_http2_decode_priority_payload(&payload, frame, err_desc)) != 0)
        return ret;
    if (frame->stream_id == payload.dependency) {
        *err_desc = "stream cannot depend on itself";
        return H2O_HTTP2_ERROR_PROTOCOL;
    }

    /* Ignore PRIORITY frames */
    return 0;
}