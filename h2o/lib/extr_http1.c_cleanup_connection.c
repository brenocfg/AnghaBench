#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * ctx; int /*<<< orphan*/ * cb; } ;
struct TYPE_6__ {int /*<<< orphan*/ * proceed_req; TYPE_2__ write_req; int /*<<< orphan*/  http1_is_persistent; } ;
struct st_h2o_http1_conn_t {scalar_t__ _unconsumed_request_size; scalar_t__ _prevreqlen; TYPE_3__ req; TYPE_1__* sock; int /*<<< orphan*/ * _req_entity_reader; } ;
struct TYPE_4__ {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_connection (struct st_h2o_http1_conn_t*,int) ; 
 int /*<<< orphan*/  h2o_buffer_consume (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  init_request (struct st_h2o_http1_conn_t*) ; 
 int /*<<< orphan*/  reqread_start (struct st_h2o_http1_conn_t*) ; 

__attribute__((used)) static void cleanup_connection(struct st_h2o_http1_conn_t *conn)
{
    if (!conn->req.http1_is_persistent) {
        /* TODO use lingering close */
        close_connection(conn, 1);
        return;
    }

    assert(conn->req.proceed_req == NULL);
    assert(conn->_req_entity_reader == NULL);

    /* handle next request */
    if (conn->_unconsumed_request_size)
        h2o_buffer_consume(&conn->sock->input, conn->_unconsumed_request_size);
    init_request(conn);
    conn->req.write_req.cb = NULL;
    conn->req.write_req.ctx = NULL;
    conn->req.proceed_req = NULL;
    conn->_prevreqlen = 0;
    conn->_unconsumed_request_size = 0;
    reqread_start(conn);
}