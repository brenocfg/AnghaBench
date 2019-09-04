#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int len; int /*<<< orphan*/ * base; } ;
struct TYPE_15__ {TYPE_5__ upgrade; } ;
struct TYPE_14__ {int /*<<< orphan*/  connected_at; TYPE_4__* ctx; } ;
struct st_h2o_http1_conn_t {TYPE_7__ req; TYPE_6__ super; TYPE_1__* sock; } ;
struct TYPE_12__ {TYPE_3__* globalconf; } ;
struct TYPE_10__ {scalar_t__ upgrade_to_http2; } ;
struct TYPE_11__ {TYPE_2__ http1; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 scalar_t__ h2o_http2_handle_upgrade (TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_lcstris (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_process_request (TYPE_7__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_request(struct st_h2o_http1_conn_t *conn)
{
    if (conn->sock->ssl == NULL && conn->req.upgrade.base != NULL && conn->super.ctx->globalconf->http1.upgrade_to_http2 &&
        conn->req.upgrade.len >= 3 && h2o_lcstris(conn->req.upgrade.base, 3, H2O_STRLIT("h2c")) &&
        (conn->req.upgrade.len == 3 ||
         (conn->req.upgrade.len == 6 && (memcmp(conn->req.upgrade.base + 3, H2O_STRLIT("-14")) == 0 ||
                                         memcmp(conn->req.upgrade.base + 3, H2O_STRLIT("-16")) == 0)))) {
        if (h2o_http2_handle_upgrade(&conn->req, conn->super.connected_at) == 0) {
            return;
        }
    }
    h2o_process_request(&conn->req);
}