#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_accept_data_t {int /*<<< orphan*/  connected_at; TYPE_6__* ctx; } ;
struct sockaddr_storage {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_10__ {struct st_h2o_accept_data_t* data; TYPE_8__* input; } ;
typedef  TYPE_1__ h2o_socket_t ;
struct TYPE_13__ {int /*<<< orphan*/  (* destroy ) (struct st_h2o_accept_data_t*) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  size; int /*<<< orphan*/  bytes; } ;
struct TYPE_11__ {int /*<<< orphan*/ * ssl_ctx; } ;

/* Variables and functions */
 TYPE_9__ accept_data_callbacks ; 
 int /*<<< orphan*/  h2o_buffer_consume (TYPE_8__**,int) ; 
 int /*<<< orphan*/  h2o_http1_accept (TYPE_6__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_close (TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_socket_setpeername (TYPE_1__*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_ssl_handshake (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_ssl_handshake_complete ; 
 int parse_proxy_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct st_h2o_accept_data_t*) ; 
 int /*<<< orphan*/  stub2 (struct st_h2o_accept_data_t*) ; 

__attribute__((used)) static void on_read_proxy_line(h2o_socket_t *sock, const char *err)
{
    struct st_h2o_accept_data_t *data = sock->data;

    if (err != NULL) {
        accept_data_callbacks.destroy(data);
        h2o_socket_close(sock);
        return;
    }

    struct sockaddr_storage addr;
    socklen_t addrlen;
    ssize_t r = parse_proxy_line(sock->input->bytes, sock->input->size, (void *)&addr, &addrlen);
    switch (r) {
    case -1: /* error, just pass the input to the next handler */
        break;
    case -2: /* incomplete */
        return;
    default:
        h2o_buffer_consume(&sock->input, r);
        if (addrlen != 0)
            h2o_socket_setpeername(sock, (void *)&addr, addrlen);
        break;
    }

    if (data->ctx->ssl_ctx != NULL) {
        h2o_socket_ssl_handshake(sock, data->ctx->ssl_ctx, NULL, h2o_iovec_init(NULL, 0), on_ssl_handshake_complete);
    } else {
        struct st_h2o_accept_data_t *data = sock->data;
        sock->data = NULL;
        h2o_http1_accept(data->ctx, sock, data->connected_at);
        accept_data_callbacks.destroy(data);
    }
}