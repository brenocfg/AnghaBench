#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* ctx; } ;
struct TYPE_9__ {int /*<<< orphan*/ * scheme; } ;
struct TYPE_11__ {int version; TYPE_3__ input; } ;
struct TYPE_10__ {TYPE_2__ super; int /*<<< orphan*/  _is_complete; TYPE_5__ req; } ;
typedef  TYPE_4__ h2o_loopback_conn_t ;
struct TYPE_7__ {int /*<<< orphan*/  loop; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_URL_SCHEME_HTTP ; 
 int /*<<< orphan*/  INT32_MAX ; 
 int /*<<< orphan*/  UV_RUN_ONCE ; 
 int /*<<< orphan*/  h2o_evloop_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_process_request (TYPE_5__*) ; 
 int /*<<< orphan*/  uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void h2o_loopback_run_loop(h2o_loopback_conn_t *conn)
{
    if (conn->req.input.scheme == NULL)
        conn->req.input.scheme = &H2O_URL_SCHEME_HTTP;
    if (conn->req.version == 0)
        conn->req.version = 0x100; /* HTTP/1.0 */

    h2o_process_request(&conn->req);

    while (!conn->_is_complete) {
#if H2O_USE_LIBUV
        uv_run(conn->super.ctx->loop, UV_RUN_ONCE);
#else
        h2o_evloop_run(conn->super.ctx->loop, INT32_MAX);
#endif
    }
}