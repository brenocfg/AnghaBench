#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ dirty_pollset; TYPE_1__* conns; } ;
typedef  TYPE_2__ serf_context_t ;
struct TYPE_10__ {scalar_t__ dirty_conn; } ;
typedef  TYPE_3__ serf_connection_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_8__ {int nelts; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 TYPE_3__* GET_CONN (TYPE_2__*,int) ; 
 int /*<<< orphan*/  serf__conn_update_pollset (TYPE_3__*) ; 

__attribute__((used)) static apr_status_t check_dirty_pollsets(serf_context_t *ctx)
{
    int i;

    /* if we're not dirty, return now. */
    if (!ctx->dirty_pollset) {
        return APR_SUCCESS;
    }

    for (i = ctx->conns->nelts; i--; ) {
        serf_connection_t *conn = GET_CONN(ctx, i);
        apr_status_t status;

        /* if this connection isn't dirty, skip it. */
        if (!conn->dirty_conn) {
            continue;
        }

        /* reset this connection's flag before we update. */
        conn->dirty_conn = 0;

        if ((status = serf__conn_update_pollset(conn)) != APR_SUCCESS)
            return status;
    }

    /* reset our context flag now */
    ctx->dirty_pollset = 0;

    return APR_SUCCESS;
}