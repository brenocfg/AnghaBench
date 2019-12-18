#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ state; } ;
struct TYPE_6__ {scalar_t__ (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  ctx; } ;
struct TYPE_7__ {size_t req_body_bytes_received; int /*<<< orphan*/ * proceed_req; TYPE_1__ write_req; } ;
struct st_h2o_http1_conn_t {TYPE_3__ _ostr_final; int /*<<< orphan*/ * _req_entity_reader; TYPE_2__ req; TYPE_4__* sock; } ;
struct TYPE_10__ {int /*<<< orphan*/  bytes; } ;
struct TYPE_9__ {TYPE_5__* input; } ;

/* Variables and functions */
 scalar_t__ OSTREAM_STATE_DONE ; 
 int /*<<< orphan*/  cleanup_connection (struct st_h2o_http1_conn_t*) ; 
 int /*<<< orphan*/  entity_read_send_error_502 (struct st_h2o_http1_conn_t*,char*,char*) ; 
 int /*<<< orphan*/  h2o_buffer_consume (TYPE_5__**,size_t) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  h2o_socket_read_stop (TYPE_4__*) ; 
 int /*<<< orphan*/  set_timeout (struct st_h2o_http1_conn_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void handle_one_body_fragment(struct st_h2o_http1_conn_t *conn, size_t fragment_size, int complete)
{
    set_timeout(conn, 0, NULL);
    h2o_socket_read_stop(conn->sock);
    if (conn->req.write_req.cb(conn->req.write_req.ctx, h2o_iovec_init(conn->sock->input->bytes, fragment_size), complete) != 0) {
        entity_read_send_error_502(conn, "Bad Gateway", "Bad Gateway");
        return;
    }
    h2o_buffer_consume(&conn->sock->input, fragment_size);
    conn->req.req_body_bytes_received += fragment_size;
    if (complete) {
        conn->req.proceed_req = NULL;
        conn->_req_entity_reader = NULL;
        if (conn->_ostr_final.state == OSTREAM_STATE_DONE) {
            cleanup_connection(conn);
        }
    }
}