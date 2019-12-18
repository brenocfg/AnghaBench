#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_12__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/  request_begin_at; } ;
struct TYPE_25__ {int /*<<< orphan*/  cb; } ;
struct TYPE_27__ {size_t header; size_t body; int /*<<< orphan*/  total; } ;
struct TYPE_26__ {int /*<<< orphan*/ * on_head; int /*<<< orphan*/ * (* on_connect ) (TYPE_8__*,int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,size_t*,TYPE_6__*,int /*<<< orphan*/ **,TYPE_7__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_33__ {TYPE_5__* ctx; TYPE_4__ timings; TYPE_14__ _timeout; TYPE_2__ bytes_written; TYPE_1__ _cb; } ;
struct TYPE_28__ {int /*<<< orphan*/  req; } ;
struct st_h2o_http1client_t {TYPE_12__* sock; TYPE_8__ super; TYPE_3__ state; int /*<<< orphan*/  _is_chunked; int /*<<< orphan*/  _body_buf; int /*<<< orphan*/ * proceed_req; int /*<<< orphan*/  _method_is_head; int /*<<< orphan*/  _origin; } ;
typedef  int /*<<< orphan*/  h2o_url_t ;
struct TYPE_31__ {size_t len; int /*<<< orphan*/ * base; } ;
typedef  TYPE_6__ h2o_iovec_t ;
struct TYPE_32__ {int* member_1; int /*<<< orphan*/ * chunked; int /*<<< orphan*/ * connection_header; TYPE_6__* proxy_protocol; TYPE_6__* member_2; TYPE_6__* member_0; } ;
typedef  TYPE_7__ h2o_httpclient_properties_t ;
typedef  int /*<<< orphan*/  h2o_header_t ;
struct TYPE_30__ {int /*<<< orphan*/  loop; int /*<<< orphan*/  io_timeout; } ;
struct TYPE_24__ {int /*<<< orphan*/  bytes_written; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  STREAM_STATE_BODY ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_6__ build_request (struct st_h2o_http1client_t*,TYPE_6__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  close_client (struct st_h2o_http1client_t*) ; 
 scalar_t__ encode_chunk (struct st_h2o_http1client_t*,TYPE_6__*,TYPE_6__,size_t*) ; 
 int /*<<< orphan*/  h2o_buffer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_buffer_try_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  h2o_gettimeofday (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_httpclient_error_internal ; 
 TYPE_6__ h2o_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_memis (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_buffer_prototype ; 
 int /*<<< orphan*/  h2o_socket_read_start (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_write (TYPE_12__*,TYPE_6__*,size_t,int /*<<< orphan*/  (*) (TYPE_12__*,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_14__*) ; 
 int /*<<< orphan*/  on_head ; 
 int /*<<< orphan*/  on_req_body_done (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_send_timeout ; 
 int /*<<< orphan*/  on_whole_request_sent (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_8__*,int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,size_t*,TYPE_6__*,int /*<<< orphan*/ **,TYPE_7__*,int /*<<< orphan*/ ) ; 

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
    h2o_iovec_t header = build_request(client, method, url, *props.connection_header, headers, num_headers);
    reqbufs[reqbufcnt++] = header;
    client->super.bytes_written.header = header.len;

    client->_is_chunked = *props.chunked;
    client->_method_is_head = h2o_memis(method.base, method.len, H2O_STRLIT("HEAD"));

    if (client->proceed_req != NULL) {
        if (body.base != NULL) {
            h2o_buffer_init(&client->_body_buf, &h2o_socket_buffer_prototype);
            if (!h2o_buffer_try_append(&client->_body_buf, body.base, body.len)) {
                on_whole_request_sent(client->sock, h2o_httpclient_error_internal);
                return;
            }
        }
        h2o_socket_write(client->sock, reqbufs, reqbufcnt, on_req_body_done);
    } else {
        if (client->_is_chunked) {
            assert(body.base != NULL);
            size_t bytes;
            reqbufcnt += encode_chunk(client, reqbufs + reqbufcnt, body, &bytes);
            client->super.bytes_written.body = bytes;
        } else if (body.base != NULL) {
            reqbufs[reqbufcnt++] = body;
            client->super.bytes_written.body = body.len;
        }
        h2o_socket_write(client->sock, reqbufs, reqbufcnt, on_whole_request_sent);
    }
    client->super.bytes_written.total = client->sock->bytes_written;

    /* TODO no need to set the timeout if all data has been written into TCP sendbuf */
    client->super._timeout.cb = on_send_timeout;
    h2o_timer_link(client->super.ctx->loop, client->super.ctx->io_timeout, &client->super._timeout);

    client->state.req = STREAM_STATE_BODY;
    client->super.timings.request_begin_at = h2o_gettimeofday(client->super.ctx->loop);

    h2o_socket_read_start(client->sock, on_head);
}