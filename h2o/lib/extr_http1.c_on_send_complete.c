#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  response_end_at; } ;
struct TYPE_11__ {int /*<<< orphan*/ * proceed_req; scalar_t__ send_server_timing; scalar_t__ http1_is_persistent; TYPE_1__ timestamps; int /*<<< orphan*/ * _ostr_top; } ;
struct TYPE_15__ {int /*<<< orphan*/  state; int /*<<< orphan*/ * chunked_buf; int /*<<< orphan*/  super; } ;
struct TYPE_14__ {TYPE_2__* ctx; } ;
struct st_h2o_http1_conn_t {TYPE_10__ req; TYPE_4__ _ostr_final; int /*<<< orphan*/  sock; TYPE_3__ super; } ;
struct TYPE_16__ {struct st_h2o_http1_conn_t* data; } ;
typedef  TYPE_5__ h2o_socket_t ;
struct TYPE_17__ {scalar_t__ len; } ;
typedef  TYPE_6__ h2o_iovec_t ;
struct TYPE_13__ {int /*<<< orphan*/  loop; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  OSTREAM_STATE_DONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cleanup_connection (struct st_h2o_http1_conn_t*) ; 
 TYPE_6__ h2o_build_server_timing_trailer (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_gettimeofday (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_write (int /*<<< orphan*/ ,TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_send_complete_post_trailers ; 

__attribute__((used)) static void on_send_complete(h2o_socket_t *sock, const char *err)
{
    struct st_h2o_http1_conn_t *conn = sock->data;

    assert(conn->req._ostr_top == &conn->_ostr_final.super);

    conn->req.timestamps.response_end_at = h2o_gettimeofday(conn->super.ctx->loop);

    if (err != NULL)
        conn->req.http1_is_persistent = 0;

    if (err == NULL && conn->req.send_server_timing && conn->_ostr_final.chunked_buf != NULL) {
        h2o_iovec_t trailer;
        if ((trailer = h2o_build_server_timing_trailer(&conn->req, H2O_STRLIT("server-timing: "), H2O_STRLIT("\r\n\r\n"))).len !=
            0) {
            h2o_socket_write(conn->sock, &trailer, 1, on_send_complete_post_trailers);
            return;
        }
    }

    /* TODO Consider if we should shut down the send side in case HTTP/1 is running without Content-Length header, as there is no
     * other way to communicate the end of the response. T-E chunked will communicate the end when HTTP/1.1 is being used. */
    conn->_ostr_final.state = OSTREAM_STATE_DONE;
    if (conn->req.proceed_req == NULL)
        cleanup_connection(conn);
}