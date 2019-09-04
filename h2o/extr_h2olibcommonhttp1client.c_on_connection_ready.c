#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  request_begin_at; } ;
struct TYPE_17__ {int /*<<< orphan*/  cb; } ;
struct TYPE_18__ {int /*<<< orphan*/ * on_head; int /*<<< orphan*/ * (* on_connect ) (TYPE_6__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,size_t*,TYPE_4__*,int /*<<< orphan*/ **,TYPE_5__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_23__ {TYPE_3__* ctx; TYPE_2__ timings; TYPE_10__ _timeout; TYPE_1__ _cb; } ;
struct st_h2o_http1client_t {TYPE_6__ super; int /*<<< orphan*/  sock; int /*<<< orphan*/  _is_chunked; int /*<<< orphan*/  _body_buf; int /*<<< orphan*/ * proceed_req; int /*<<< orphan*/  _method_is_head; int /*<<< orphan*/  _origin; } ;
typedef  int /*<<< orphan*/  h2o_url_t ;
struct TYPE_21__ {int /*<<< orphan*/ * base; int /*<<< orphan*/  len; } ;
typedef  TYPE_4__ h2o_iovec_t ;
struct TYPE_22__ {int* member_1; int /*<<< orphan*/ * chunked; int /*<<< orphan*/ * connection_header; TYPE_4__* proxy_protocol; TYPE_4__* member_2; TYPE_4__* member_0; } ;
typedef  TYPE_5__ h2o_httpclient_properties_t ;
typedef  int /*<<< orphan*/  h2o_header_t ;
struct TYPE_20__ {int /*<<< orphan*/  loop; int /*<<< orphan*/  io_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_4__ build_request (struct st_h2o_http1client_t*,TYPE_4__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  close_client (struct st_h2o_http1client_t*) ; 
 scalar_t__ encode_chunk (struct st_h2o_http1client_t*,TYPE_4__*,TYPE_4__) ; 
 scalar_t__ h2o_buffer_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_buffer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_gettimeofday (int /*<<< orphan*/ ) ; 
 TYPE_4__ h2o_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_memis (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_buffer_prototype ; 
 int /*<<< orphan*/  h2o_socket_write (int /*<<< orphan*/ ,TYPE_4__*,size_t,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,char*)) ; 
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_10__*) ; 
 int /*<<< orphan*/  on_req_body_done (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  on_send_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  on_send_timeout ; 
 int /*<<< orphan*/ * stub1 (TYPE_6__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,size_t*,TYPE_4__*,int /*<<< orphan*/ **,TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_connection_ready(struct st_h2o_http1client_t *client)
{
    h2o_iovec_t proxy_protocol = h2o_iovec_init(NULL, 0);
    int chunked = 0;
    h2o_iovec_t connection_header = h2o_iovec_init(NULL, 0);
    h2o_httpclient_properties_t props = {
        &proxy_protocol,
        &chunked,
        &connection_header,
    };
    h2o_iovec_t method;
    h2o_url_t url;
    h2o_header_t *headers;
    size_t num_headers;
    h2o_iovec_t body;

    client->super._cb.on_head = client->super._cb.on_connect(&client->super, NULL, &method, &url, (const h2o_header_t **)&headers,
                                                             &num_headers, &body, &client->proceed_req, &props, client->_origin);

    if (client->super._cb.on_head == NULL) {
        close_client(client);
        return;
    }

    h2o_iovec_t reqbufs[3];
    size_t reqbufcnt = 0;
    if (props.proxy_protocol->base != NULL)
        reqbufs[reqbufcnt++] = *props.proxy_protocol;
    reqbufs[reqbufcnt++] = build_request(client, method, url, *props.connection_header, headers, num_headers);

    client->_is_chunked = *props.chunked;
    client->_method_is_head = h2o_memis(method.base, method.len, H2O_STRLIT("HEAD"));

    if (client->proceed_req != NULL) {
        if (body.base != NULL) {
            h2o_buffer_init(&client->_body_buf, &h2o_socket_buffer_prototype);
            if (h2o_buffer_append(&client->_body_buf, body.base, body.len) == 0) {
                on_send_request(client->sock, "Internal error");
                return;
            }
        }
        h2o_socket_write(client->sock, reqbufs, reqbufcnt, on_req_body_done);
    } else {
        if (client->_is_chunked) {
            assert(body.base != NULL);
            reqbufcnt += encode_chunk(client, reqbufs + reqbufcnt, body);
        } else if (body.base != NULL) {
            reqbufs[reqbufcnt++] = body;
        }
        h2o_socket_write(client->sock, reqbufs, reqbufcnt, on_send_request);
    }

    /* TODO no need to set the timeout if all data has been written into TCP sendbuf */
    client->super._timeout.cb = on_send_timeout;
    h2o_timer_link(client->super.ctx->loop, client->super.ctx->io_timeout, &client->super._timeout);

    client->super.timings.request_begin_at = h2o_gettimeofday(client->super.ctx->loop);
}