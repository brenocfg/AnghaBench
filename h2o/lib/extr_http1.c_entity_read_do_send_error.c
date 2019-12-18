#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ state; } ;
struct TYPE_8__ {scalar_t__ http1_is_persistent; int /*<<< orphan*/ * _generator; int /*<<< orphan*/ * proceed_req; } ;
struct TYPE_6__ {TYPE_1__* ctx; } ;
struct st_h2o_http1_conn_t {TYPE_3__ _ostr_final; TYPE_4__ req; TYPE_2__ super; int /*<<< orphan*/  sock; int /*<<< orphan*/ * _req_entity_reader; } ;
struct TYPE_5__ {int /*<<< orphan*/ * emitted_error_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_SEND_ERROR_HTTP1_CLOSE_CONNECTION ; 
 scalar_t__ OSTREAM_STATE_DONE ; 
 scalar_t__ OSTREAM_STATE_HEAD ; 
 int /*<<< orphan*/  cleanup_connection (struct st_h2o_http1_conn_t*) ; 
 int /*<<< orphan*/  h2o_send_error_generic (TYPE_4__*,int,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_read_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_timeout (struct st_h2o_http1_conn_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void entity_read_do_send_error(struct st_h2o_http1_conn_t *conn, int status, size_t status_error_index, const char *reason,
                                      const char *body)
{
    conn->req.proceed_req = NULL;
    conn->_req_entity_reader = NULL;
    set_timeout(conn, 0, NULL);
    h2o_socket_read_stop(conn->sock);
    /* FIXME We should check if `h2o_proceed_request` has been called, rather than trying to guess if we have (I'm unsure if the
     * contract is for h2o_req_t::_generator to become non-NULL immediately after `h2o_proceed_request` is being called). */
    if (conn->req._generator == NULL && conn->_ostr_final.state == OSTREAM_STATE_HEAD) {
        conn->super.ctx->emitted_error_status[status_error_index]++;
        h2o_send_error_generic(&conn->req, status, reason, body, H2O_SEND_ERROR_HTTP1_CLOSE_CONNECTION);
    } else {
        conn->req.http1_is_persistent = 0;
        if (conn->_ostr_final.state == OSTREAM_STATE_DONE)
            cleanup_connection(conn);
    }
}