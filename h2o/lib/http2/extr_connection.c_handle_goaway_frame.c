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
typedef  int /*<<< orphan*/  h2o_http2_goaway_payload_t ;
typedef  int /*<<< orphan*/  h2o_http2_frame_t ;
struct TYPE_4__ {int max_open; } ;
struct TYPE_5__ {TYPE_1__ push_stream_ids; } ;
typedef  TYPE_2__ h2o_http2_conn_t ;

/* Variables and functions */
 int h2o_http2_decode_goaway_payload (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static int handle_goaway_frame(h2o_http2_conn_t *conn, h2o_http2_frame_t *frame, const char **err_desc)
{
    h2o_http2_goaway_payload_t payload;
    int ret;

    if ((ret = h2o_http2_decode_goaway_payload(&payload, frame, err_desc)) != 0)
        return ret;

    /* stop opening new push streams hereafter */
    conn->push_stream_ids.max_open = 0x7ffffffe;

    return 0;
}