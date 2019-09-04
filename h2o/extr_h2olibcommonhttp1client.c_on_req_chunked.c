#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int (* on_body ) (TYPE_9__*,char*) ;} ;
struct TYPE_16__ {void* response_end_at; } ;
struct TYPE_21__ {int /*<<< orphan*/  _timeout; TYPE_6__* ctx; TYPE_5__ _cb; TYPE_4__ timings; } ;
struct TYPE_14__ {int /*<<< orphan*/  decoder; } ;
struct TYPE_15__ {TYPE_2__ chunked; } ;
struct st_h2o_http1client_t {TYPE_9__ super; scalar_t__ _do_keepalive; TYPE_3__ _body_decoder; TYPE_1__* sock; } ;
struct TYPE_19__ {size_t bytes_read; struct st_h2o_http1client_t* data; } ;
typedef  TYPE_7__ h2o_socket_t ;
struct TYPE_20__ {size_t bytes; size_t size; } ;
typedef  TYPE_8__ h2o_buffer_t ;
struct TYPE_18__ {int /*<<< orphan*/  io_timeout; int /*<<< orphan*/  loop; } ;
struct TYPE_13__ {TYPE_8__* input; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_client (struct st_h2o_http1client_t*) ; 
 int /*<<< orphan*/  do_update_window (TYPE_9__*) ; 
 void* h2o_gettimeofday (int /*<<< orphan*/ ) ; 
 char* h2o_httpclient_error_is_eos ; 
 char const* h2o_socket_error_closed ; 
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_body_error (struct st_h2o_http1client_t*,char*) ; 
 int phr_decode_chunked (int /*<<< orphan*/ *,size_t,size_t*) ; 
 int /*<<< orphan*/  phr_decode_chunked_is_in_data (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_9__*,char*) ; 
 int stub2 (TYPE_9__*,char const*) ; 

__attribute__((used)) static void on_req_chunked(h2o_socket_t *sock, const char *err)
{
    struct st_h2o_http1client_t *client = sock->data;
    h2o_buffer_t *inbuf;

    h2o_timer_unlink(&client->super._timeout);

    if (err != NULL) {
        if (err == h2o_socket_error_closed && !phr_decode_chunked_is_in_data(&client->_body_decoder.chunked.decoder)) {
            /*
             * if the peer closed after a full chunk, treat this
             * as if the transfer had complete, browsers appear to ignore
             * a missing 0\r\n chunk
             */
            client->_do_keepalive = 0;
            client->super.timings.response_end_at = h2o_gettimeofday(client->super.ctx->loop);
            client->super._cb.on_body(&client->super, h2o_httpclient_error_is_eos);
            close_client(client);
        } else {
            on_body_error(client, "I/O error (body; chunked)");
        }
        return;
    }

    inbuf = client->sock->input;
    if (sock->bytes_read != 0) {
        const char *errstr;
        int cb_ret;
        size_t newsz = sock->bytes_read;

        switch (phr_decode_chunked(&client->_body_decoder.chunked.decoder, inbuf->bytes + inbuf->size - newsz, &newsz)) {
        case -1: /* error */
            newsz = sock->bytes_read;
            client->_do_keepalive = 0;
            errstr = "failed to parse the response (chunked)";
            break;
        case -2: /* incomplete */
            errstr = NULL;
            break;
        default: /* complete, with garbage on tail; should disable keepalive */
            client->_do_keepalive = 0;
        /* fallthru */
        case 0: /* complete */
            errstr = h2o_httpclient_error_is_eos;
            client->super.timings.response_end_at = h2o_gettimeofday(client->super.ctx->loop);
            break;
        }
        inbuf->size -= sock->bytes_read - newsz;
        cb_ret = client->super._cb.on_body(&client->super, errstr);
        if (errstr != NULL) {
            close_client(client);
            return;
        } else if (cb_ret != 0) {
            client->_do_keepalive = 0;
            close_client(client);
            return;
        }
        do_update_window(&client->super);
    }

    h2o_timer_link(client->super.ctx->loop, client->super.ctx->io_timeout, &client->super._timeout);
}