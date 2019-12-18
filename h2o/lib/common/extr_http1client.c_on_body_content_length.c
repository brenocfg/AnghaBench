#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {int (* on_body ) (TYPE_10__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_16__ {int /*<<< orphan*/  response_end_at; } ;
struct TYPE_13__ {int /*<<< orphan*/  _timeout; TYPE_8__* ctx; TYPE_6__ _cb; TYPE_3__ timings; } ;
struct TYPE_20__ {scalar_t__ res; } ;
struct TYPE_17__ {scalar_t__ bytesleft; } ;
struct TYPE_18__ {TYPE_4__ content_length; } ;
struct st_h2o_http1client_t {TYPE_10__ super; scalar_t__ _do_keepalive; TYPE_7__ state; TYPE_5__ _body_decoder; TYPE_2__* sock; } ;
struct TYPE_22__ {scalar_t__ bytes_read; struct st_h2o_http1client_t* data; } ;
typedef  TYPE_9__ h2o_socket_t ;
struct TYPE_21__ {int /*<<< orphan*/  io_timeout; int /*<<< orphan*/  loop; } ;
struct TYPE_15__ {TYPE_1__* input; } ;
struct TYPE_14__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 scalar_t__ STREAM_STATE_CLOSED ; 
 int /*<<< orphan*/  close_client (struct st_h2o_http1client_t*) ; 
 int /*<<< orphan*/  close_response (struct st_h2o_http1client_t*) ; 
 int /*<<< orphan*/  do_update_window (TYPE_10__*) ; 
 int /*<<< orphan*/  h2o_gettimeofday (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_httpclient_error_io ; 
 int /*<<< orphan*/ * h2o_httpclient_error_is_eos ; 
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_error (struct st_h2o_http1client_t*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_10__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_body_content_length(h2o_socket_t *sock, const char *err)
{
    struct st_h2o_http1client_t *client = sock->data;

    h2o_timer_unlink(&client->super._timeout);

    if (err != NULL) {
        on_error(client, h2o_httpclient_error_io);
        return;
    }

    if (sock->bytes_read != 0 || client->_body_decoder.content_length.bytesleft == 0) {
        int ret;
        if (client->_body_decoder.content_length.bytesleft <= sock->bytes_read) {
            if (client->_body_decoder.content_length.bytesleft < sock->bytes_read) {
                /* remove the trailing garbage from buf, and disable keepalive */
                client->sock->input->size -= sock->bytes_read - client->_body_decoder.content_length.bytesleft;
                client->_do_keepalive = 0;
            }
            client->_body_decoder.content_length.bytesleft = 0;
            client->state.res = STREAM_STATE_CLOSED;
            client->super.timings.response_end_at = h2o_gettimeofday(client->super.ctx->loop);
        } else {
            client->_body_decoder.content_length.bytesleft -= sock->bytes_read;
        }
        ret = client->super._cb.on_body(&client->super,
                                        client->state.res == STREAM_STATE_CLOSED ? h2o_httpclient_error_is_eos : NULL);
        if (client->state.res == STREAM_STATE_CLOSED) {
            close_response(client);
            return;
        } else if (ret != 0) {
            client->_do_keepalive = 0;
            close_client(client);
            return;
        }
        do_update_window(&client->super);
    }

    h2o_timer_link(client->super.ctx->loop, client->super.ctx->io_timeout, &client->super._timeout);
}