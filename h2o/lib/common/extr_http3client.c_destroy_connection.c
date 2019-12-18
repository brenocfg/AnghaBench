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
struct TYPE_6__ {struct st_h2o_http3client_conn_t* base; } ;
struct TYPE_5__ {struct st_h2o_http3client_conn_t* base; } ;
struct TYPE_7__ {TYPE_2__ authority; TYPE_1__ host; } ;
struct TYPE_8__ {TYPE_3__ origin_url; } ;
struct st_h2o_http3client_conn_t {int /*<<< orphan*/  super; TYPE_4__ server; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * getaddr_req; int /*<<< orphan*/  clients_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct st_h2o_http3client_conn_t*) ; 
 int /*<<< orphan*/  h2o_hostinfo_getaddr_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_http3_dispose_conn (int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_linklist_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_linklist_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_connection(struct st_h2o_http3client_conn_t *conn)
{
    if (h2o_linklist_is_linked(&conn->clients_link))
        h2o_linklist_unlink(&conn->clients_link);
    /* FIXME pending_requests */
    if (conn->getaddr_req != NULL)
        h2o_hostinfo_getaddr_cancel(conn->getaddr_req);
    h2o_timer_unlink(&conn->timeout);
    free(conn->server.origin_url.host.base);
    free(conn->server.origin_url.authority.base);
    h2o_http3_dispose_conn(&conn->super);
    free(conn);
}