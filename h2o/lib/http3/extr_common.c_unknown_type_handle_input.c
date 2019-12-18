#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
struct st_h2o_http3_ingress_unistream_t {int (* handle_input ) (TYPE_3__*,struct st_h2o_http3_ingress_unistream_t*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,char const**) ;int /*<<< orphan*/  quic; } ;
struct TYPE_10__ {struct st_h2o_http3_ingress_unistream_t* qpack_decoder; struct st_h2o_http3_ingress_unistream_t* qpack_encoder; struct st_h2o_http3_ingress_unistream_t* control; } ;
struct TYPE_11__ {TYPE_1__ ingress; } ;
struct TYPE_12__ {TYPE_2__ _control_streams; } ;
typedef  TYPE_3__ h2o_http3_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_HTTP3_ERROR_STREAM_CREATION ; 
#define  H2O_HTTP3_STREAM_TYPE_CONTROL 130 
#define  H2O_HTTP3_STREAM_TYPE_QPACK_DECODER 129 
#define  H2O_HTTP3_STREAM_TYPE_QPACK_ENCODER 128 
 int UINT64_MAX ; 
 int control_stream_handle_input (TYPE_3__*,struct st_h2o_http3_ingress_unistream_t*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,char const**) ; 
 int qpack_decoder_stream_handle_input (TYPE_3__*,struct st_h2o_http3_ingress_unistream_t*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,char const**) ; 
 int qpack_encoder_stream_handle_input (TYPE_3__*,struct st_h2o_http3_ingress_unistream_t*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,char const**) ; 
 int quicly_decodev (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  quicly_request_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*,struct st_h2o_http3_ingress_unistream_t*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,char const**) ; 
 int unknown_stream_type_handle_input (TYPE_3__*,struct st_h2o_http3_ingress_unistream_t*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,char const**) ; 

__attribute__((used)) static int unknown_type_handle_input(h2o_http3_conn_t *conn, struct st_h2o_http3_ingress_unistream_t *stream, const uint8_t **src,
                                     const uint8_t *src_end, const char **err_desc)
{
    if (*src == src_end) {
        /* a sender is allowed to close or reset a unidirectional stream */
        return 0;
    }

    /* read the type, or just return if incomplete */
    uint64_t type;
    if ((type = quicly_decodev(src, src_end)) == UINT64_MAX)
        return 0;

    switch (type) {
    case H2O_HTTP3_STREAM_TYPE_CONTROL:
        conn->_control_streams.ingress.control = stream;
        stream->handle_input = control_stream_handle_input;
        break;
    case H2O_HTTP3_STREAM_TYPE_QPACK_ENCODER:
        conn->_control_streams.ingress.qpack_encoder = stream;
        stream->handle_input = qpack_encoder_stream_handle_input;
        break;
    case H2O_HTTP3_STREAM_TYPE_QPACK_DECODER:
        conn->_control_streams.ingress.qpack_decoder = stream;
        stream->handle_input = qpack_decoder_stream_handle_input;
        break;
    default:
        quicly_request_stop(stream->quic, H2O_HTTP3_ERROR_STREAM_CREATION);
        stream->handle_input =
            unknown_stream_type_handle_input; /* TODO reconsider quicly API; do we need to read data after sending STOP_SENDING? */
        break;
    }

    return stream->handle_input(conn, stream, src, src_end, err_desc);
}