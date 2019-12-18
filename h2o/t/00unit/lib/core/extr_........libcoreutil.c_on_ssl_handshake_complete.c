#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct st_h2o_accept_data_t {int /*<<< orphan*/  connected_at; TYPE_11__* ctx; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_20__ {struct st_h2o_accept_data_t* data; } ;
typedef  TYPE_3__ h2o_socket_t ;
struct TYPE_21__ {scalar_t__ len; int /*<<< orphan*/  base; } ;
typedef  TYPE_4__ h2o_iovec_t ;
struct TYPE_18__ {int /*<<< orphan*/  alpn_h1; int /*<<< orphan*/  alpn_h2; int /*<<< orphan*/  handshake_accum_time_full; int /*<<< orphan*/  handshake_full; int /*<<< orphan*/  handshake_accum_time_resume; int /*<<< orphan*/  handshake_resume; int /*<<< orphan*/  errors; } ;
struct TYPE_19__ {TYPE_1__ ssl; int /*<<< orphan*/  loop; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* destroy ) (struct st_h2o_accept_data_t*) ;} ;
struct TYPE_16__ {TYPE_2__* ctx; } ;

/* Variables and functions */
 TYPE_15__ accept_data_callbacks ; 
 struct timeval h2o_gettimeofday (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_http1_accept (TYPE_11__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_http2_accept (TYPE_11__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* h2o_http2_alpn_protocols ; 
 int /*<<< orphan*/  h2o_socket_close (TYPE_3__*) ; 
 scalar_t__ h2o_socket_get_ssl_session_reused (TYPE_3__*) ; 
 TYPE_4__ h2o_socket_ssl_get_selected_protocol (TYPE_3__*) ; 
 scalar_t__ h2o_timeval_subtract (int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct st_h2o_accept_data_t*) ; 

__attribute__((used)) static void on_ssl_handshake_complete(h2o_socket_t *sock, const char *err)
{
    struct st_h2o_accept_data_t *data = sock->data;
    sock->data = NULL;

    if (err != NULL) {
        ++data->ctx->ctx->ssl.errors;
        h2o_socket_close(sock);
        goto Exit;
    }

    /* stats for handshake */
    struct timeval handshake_completed_at = h2o_gettimeofday(data->ctx->ctx->loop);
    int64_t handshake_time = h2o_timeval_subtract(&data->connected_at, &handshake_completed_at);
    if (h2o_socket_get_ssl_session_reused(sock)) {
        ++data->ctx->ctx->ssl.handshake_resume;
        data->ctx->ctx->ssl.handshake_accum_time_resume += handshake_time;
    } else {
        ++data->ctx->ctx->ssl.handshake_full;
        data->ctx->ctx->ssl.handshake_accum_time_full += handshake_time;
    }

    h2o_iovec_t proto = h2o_socket_ssl_get_selected_protocol(sock);
    const h2o_iovec_t *ident;
    for (ident = h2o_http2_alpn_protocols; ident->len != 0; ++ident) {
        if (proto.len == ident->len && memcmp(proto.base, ident->base, proto.len) == 0) {
            /* connect as http2 */
            ++data->ctx->ctx->ssl.alpn_h2;
            h2o_http2_accept(data->ctx, sock, data->connected_at);
            goto Exit;
        }
    }
    /* connect as http1 */
    if (proto.len != 0)
        ++data->ctx->ctx->ssl.alpn_h1;
    h2o_http1_accept(data->ctx, sock, data->connected_at);

Exit:
    accept_data_callbacks.destroy(data);
}