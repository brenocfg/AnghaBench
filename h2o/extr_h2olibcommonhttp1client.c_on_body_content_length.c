#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int (* on_body ) (TYPE_9__*,char const*) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  response_end_at; } ;
struct TYPE_20__ {int /*<<< orphan*/  _timeout; TYPE_7__* ctx; TYPE_6__ _cb; TYPE_3__ timings; } ;
struct TYPE_15__ {scalar_t__ bytesleft; } ;
struct TYPE_16__ {TYPE_4__ content_length; } ;
struct st_h2o_http1client_t {TYPE_9__ super; scalar_t__ _do_keepalive; TYPE_5__ _body_decoder; TYPE_2__* sock; } ;
struct TYPE_19__ {scalar_t__ bytes_read; struct st_h2o_http1client_t* data; } ;
typedef  TYPE_8__ h2o_socket_t ;
struct TYPE_18__ {int /*<<< orphan*/  io_timeout; int /*<<< orphan*/  loop; } ;
struct TYPE_13__ {TYPE_1__* input; } ;
struct TYPE_12__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_client (struct st_h2o_http1client_t*) ; 
 int /*<<< orphan*/  do_update_window (TYPE_9__*) ; 
 int /*<<< orphan*/  h2o_gettimeofday (int /*<<< orphan*/ ) ; 
 char const* h2o_httpclient_error_is_eos ; 
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_body_error (struct st_h2o_http1client_t*,char*) ; 
 int stub1 (TYPE_9__*,char const*) ; 

__attribute__((used)) static void on_body_content_length(h2o_socket_t *sock, const char *err)
{
    struct st_h2o_http1client_t *client = sock->data;

    h2o_timer_unlink(&client->super._timeout);

    if (err != NULL) {
        on_body_error(client, "I/O error (body; content-length)");
        return;
    }

    if (sock->bytes_read != 0 || client->_body_decoder.content_length.bytesleft == 0) {
        const char *errstr;
        int ret;
        if (client->_body_decoder.content_length.bytesleft <= sock->bytes_read) {
            if (client->_body_decoder.content_length.bytesleft < sock->bytes_read) {
                /* remove the trailing garbage from buf, and disable keepalive */
                client->sock->input->size -= sock->bytes_read - client->_body_decoder.content_length.bytesleft;
                client->_do_keepalive = 0;
            }
            client->_body_decoder.content_length.bytesleft = 0;
            errstr = h2o_httpclient_error_is_eos;
            client->super.timings.response_end_at = h2o_gettimeofday(client->super.ctx->loop);
        } else {
            client->_body_decoder.content_length.bytesleft -= sock->bytes_read;
            errstr = NULL;
        }
        ret = client->super._cb.on_body(&client->super, errstr);
        if (errstr == h2o_httpclient_error_is_eos) {
            close_client(client);
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