#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_25__ ;
typedef  struct TYPE_30__   TYPE_24__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_14__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct init_ebpf_key_info_t {int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  scid ;
struct TYPE_29__ {int /*<<< orphan*/  encrypted; } ;
struct TYPE_32__ {TYPE_1__ dest; int /*<<< orphan*/  src; } ;
struct TYPE_28__ {scalar_t__ len; } ;
struct TYPE_34__ {TYPE_2__ cid; TYPE_14__ token; } ;
typedef  TYPE_4__ quicly_decoded_packet_t ;
typedef  int /*<<< orphan*/  quicly_datagram_t ;
struct TYPE_35__ {int /*<<< orphan*/  is_retry; } ;
typedef  TYPE_5__ quicly_address_token_plaintext_t ;
struct TYPE_36__ {int /*<<< orphan*/  sa; } ;
typedef  TYPE_6__ quicly_address_t ;
typedef  int /*<<< orphan*/  ptls_aead_context_t ;
struct TYPE_30__ {TYPE_12__* quic; int /*<<< orphan*/  loop; } ;
struct TYPE_37__ {int send_retry; TYPE_24__ super; } ;
typedef  TYPE_7__ h2o_http3_server_ctx_t ;
typedef  int /*<<< orphan*/  h2o_http3_ctx_t ;
typedef  int /*<<< orphan*/  h2o_http3_conn_t ;
struct TYPE_38__ {int quic_send_retry; int /*<<< orphan*/  skip_tracing; } ;
typedef  TYPE_8__ h2o_ebpf_map_value_t ;
struct TYPE_33__ {int /*<<< orphan*/  conn_callbacks; } ;
struct TYPE_31__ {scalar_t__ max_connections; scalar_t__ max_quic_connections; TYPE_3__ quic; } ;
struct TYPE_27__ {TYPE_11__* packet_allocator; } ;
struct TYPE_26__ {int /*<<< orphan*/  (* free_packet ) (TYPE_11__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
#define  H2O_EBPF_QUIC_SEND_RETRY_OFF 129 
#define  H2O_EBPF_QUIC_SEND_RETRY_ON 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_25__ conf ; 
 int /*<<< orphan*/  h2o_http3_send_datagram (TYPE_24__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * h2o_http3_server_accept (TYPE_7__*,TYPE_6__*,TYPE_6__*,TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_8__ h2o_socket_ebpf_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct init_ebpf_key_info_t*) ; 
 int /*<<< orphan*/  init_ebpf_key_info ; 
 scalar_t__ num_connections (int) ; 
 scalar_t__ num_quic_connections (int) ; 
 int /*<<< orphan*/  num_sessions (int) ; 
 int /*<<< orphan*/  ptls_iovec_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptls_openssl_random_bytes (int /*<<< orphan*/ *,int) ; 
 scalar_t__ quic_decrypt_address_token (TYPE_5__*,TYPE_14__) ; 
 int /*<<< orphan*/ * quic_get_address_token_encryptor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * quicly_send_retry (TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_11__*,int /*<<< orphan*/ *) ; 
 scalar_t__ validate_token (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static h2o_http3_conn_t *on_http3_accept(h2o_http3_ctx_t *_ctx, quicly_address_t *destaddr, quicly_address_t *srcaddr,
                                         quicly_decoded_packet_t *packet)
{
    h2o_http3_server_ctx_t *ctx = (void *)_ctx;
    struct init_ebpf_key_info_t ebpf_keyinfo = {&destaddr->sa, &srcaddr->sa};
    h2o_ebpf_map_value_t ebpf_value = h2o_socket_ebpf_lookup(ctx->super.loop, init_ebpf_key_info, &ebpf_keyinfo);
    quicly_address_token_plaintext_t *token = NULL, token_buf;
    h2o_http3_conn_t *conn;

    /* just drop when handling too many connections */
    if (num_connections(0) >= conf.max_connections || num_quic_connections(0) >= conf.max_quic_connections)
        return NULL;

    /* handle retry, setting `token` to a non-NULL pointer if contains a valid token */
    if (packet->token.len != 0) {
        if (quic_decrypt_address_token(&token_buf, packet->token) == 0 &&
            validate_token(ctx, &srcaddr->sa, packet->cid.src, packet->cid.dest.encrypted, &token_buf))
            token = &token_buf;
    }

    /* send retry if necessary */
    if (token == NULL || !token->is_retry) {
        int send_retry = ctx->send_retry;
        switch (ebpf_value.quic_send_retry) {
        case H2O_EBPF_QUIC_SEND_RETRY_ON:
            send_retry = 1;
            break;
        case H2O_EBPF_QUIC_SEND_RETRY_OFF:
            send_retry = 0;
            break;
        default:
            break;
        }
        if (send_retry) {
            uint8_t scid[16], token_prefix;
            ptls_openssl_random_bytes(scid, sizeof(scid));
            ptls_aead_context_t *aead = quic_get_address_token_encryptor(&token_prefix);
            quicly_datagram_t *rp = quicly_send_retry(ctx->super.quic, aead, &srcaddr->sa, packet->cid.src, &destaddr->sa,
                                                      ptls_iovec_init(scid, sizeof(scid)), packet->cid.dest.encrypted,
                                                      ptls_iovec_init(&token_prefix, 1), ptls_iovec_init(NULL, 0));
            assert(rp != NULL);
            h2o_http3_send_datagram(&ctx->super, rp);
            ctx->super.quic->packet_allocator->free_packet(ctx->super.quic->packet_allocator, rp);
            return NULL;
        }
    }

    /* accept the connection */
    if ((conn = h2o_http3_server_accept(ctx, destaddr, srcaddr, packet, token, ebpf_value.skip_tracing,
                                        &conf.quic.conn_callbacks)) == NULL)
        return NULL;
    num_connections(1);
    num_quic_connections(1);
    num_sessions(1);
    return conn;
}