#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_http3_egress_unistream_t {int /*<<< orphan*/  quic; int /*<<< orphan*/  sendbuf; } ;
struct TYPE_5__ {struct st_h2o_http3_egress_unistream_t* qpack_encoder; } ;
struct TYPE_6__ {TYPE_1__ egress; } ;
struct TYPE_7__ {TYPE_2__ _control_streams; } ;
typedef  TYPE_3__ h2o_http3_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_HTTP3_CHECK_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_buffer_append (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  quicly_stream_sync_sendbuf (int /*<<< orphan*/ ,int) ; 

void h2o_http3_send_qpack_header_ack(h2o_http3_conn_t *conn, const void *bytes, size_t len)
{
    struct st_h2o_http3_egress_unistream_t *stream = conn->_control_streams.egress.qpack_encoder;

    assert(stream != NULL);
    h2o_buffer_append(&stream->sendbuf, bytes, len);
    H2O_HTTP3_CHECK_SUCCESS(quicly_stream_sync_sendbuf(stream->quic, 1));
}