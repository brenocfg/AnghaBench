#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  _link; } ;
typedef  TYPE_1__ h2o_http2_stream_t ;
struct TYPE_8__ {int /*<<< orphan*/  _pending_reqs; } ;
typedef  TYPE_2__ h2o_http2_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_linklist_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_pending_requests (TYPE_2__*) ; 
 int /*<<< orphan*/  update_idle_timeout (TYPE_2__*) ; 

__attribute__((used)) static void execute_or_enqueue_request_core(h2o_http2_conn_t *conn, h2o_http2_stream_t *stream)
{
    /* TODO schedule the pending reqs using the scheduler */
    h2o_linklist_insert(&conn->_pending_reqs, &stream->_link);

    run_pending_requests(conn);
    update_idle_timeout(conn);
}