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
typedef  int /*<<< orphan*/  uint8_t ;
struct st_h2o_http3_ingress_unistream_t {int dummy; } ;
struct TYPE_9__ {scalar_t__ type; int /*<<< orphan*/  length; int /*<<< orphan*/  payload; } ;
typedef  TYPE_2__ h2o_http3_read_frame_t ;
struct TYPE_10__ {TYPE_1__* callbacks; int /*<<< orphan*/  quic; } ;
typedef  TYPE_3__ h2o_http3_conn_t ;
struct TYPE_8__ {int (* handle_control_stream_frame ) (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ;} ;

/* Variables and functions */
 int H2O_HTTP3_ERROR_FRAME_UNEXPECTED ; 
 int H2O_HTTP3_ERROR_INCOMPLETE ; 
 scalar_t__ H2O_HTTP3_FRAME_TYPE_DATA ; 
 scalar_t__ H2O_HTTP3_FRAME_TYPE_SETTINGS ; 
 int /*<<< orphan*/  H2O_HTTP3_STREAM_TYPE_CONTROL ; 
 int h2o_http3_has_received_settings (TYPE_3__*) ; 
 int h2o_http3_read_frame (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,char const**) ; 
 int /*<<< orphan*/  quicly_is_client (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static int control_stream_handle_input(h2o_http3_conn_t *conn, struct st_h2o_http3_ingress_unistream_t *stream, const uint8_t **src,
                                       const uint8_t *src_end, const char **err_desc)
{
    h2o_http3_read_frame_t frame;
    int ret;

    do {
        if ((ret = h2o_http3_read_frame(&frame, quicly_is_client(conn->quic), H2O_HTTP3_STREAM_TYPE_CONTROL, src, src_end,
                                        err_desc)) != 0) {
            if (ret == H2O_HTTP3_ERROR_INCOMPLETE)
                ret = 0;
            break;
        }
        if (h2o_http3_has_received_settings(conn) == (frame.type == H2O_HTTP3_FRAME_TYPE_SETTINGS) ||
            frame.type == H2O_HTTP3_FRAME_TYPE_DATA)
            return H2O_HTTP3_ERROR_FRAME_UNEXPECTED;
        if ((ret = conn->callbacks->handle_control_stream_frame(conn, frame.type, frame.payload, frame.length, err_desc)) != 0)
            break;
    } while (*src != src_end);

    return ret;
}