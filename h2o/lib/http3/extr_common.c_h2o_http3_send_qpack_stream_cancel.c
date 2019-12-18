#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct st_h2o_http3_egress_unistream_t {int /*<<< orphan*/  quic; TYPE_8__* sendbuf; } ;
typedef  int /*<<< orphan*/  quicly_stream_id_t ;
struct TYPE_12__ {int /*<<< orphan*/ * base; } ;
typedef  TYPE_4__ h2o_iovec_t ;
struct TYPE_9__ {int /*<<< orphan*/  dec; } ;
struct TYPE_10__ {struct st_h2o_http3_egress_unistream_t* qpack_decoder; } ;
struct TYPE_11__ {TYPE_2__ egress; } ;
struct TYPE_13__ {TYPE_1__ qpack; TYPE_3__ _control_streams; } ;
typedef  TYPE_5__ h2o_http3_conn_t ;
struct TYPE_14__ {scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ H2O_HPACK_ENCODE_INT_MAX_LENGTH ; 
 int /*<<< orphan*/  H2O_HTTP3_CHECK_SUCCESS (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_4__ h2o_buffer_reserve (TYPE_8__**,scalar_t__) ; 
 scalar_t__ h2o_qpack_decoder_send_stream_cancel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ quicly_stream_sync_sendbuf (int /*<<< orphan*/ ,int) ; 

void h2o_http3_send_qpack_stream_cancel(h2o_http3_conn_t *conn, quicly_stream_id_t stream_id)
{
    struct st_h2o_http3_egress_unistream_t *stream = conn->_control_streams.egress.qpack_decoder;

    /* allocate and write */
    h2o_iovec_t buf = h2o_buffer_reserve(&stream->sendbuf, stream->sendbuf->size + H2O_HPACK_ENCODE_INT_MAX_LENGTH);
    assert(buf.base != NULL);
    stream->sendbuf->size += h2o_qpack_decoder_send_stream_cancel(conn->qpack.dec, (uint8_t *)buf.base, stream_id);

    /* notify the transport */
    H2O_HTTP3_CHECK_SUCCESS(quicly_stream_sync_sendbuf(stream->quic, 1) == 0);
}