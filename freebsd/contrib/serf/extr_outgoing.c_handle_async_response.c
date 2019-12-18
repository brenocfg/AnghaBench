#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * current_async_response; int /*<<< orphan*/  async_handler_baton; int /*<<< orphan*/  (* async_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  async_acceptor_baton; int /*<<< orphan*/  stream; int /*<<< orphan*/ * (* async_acceptor ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ serf_connection_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  serf_bucket_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_status_t handle_async_response(serf_connection_t *conn,
                                          apr_pool_t *pool)
{
    apr_status_t status;

    if (conn->current_async_response == NULL) {
        conn->current_async_response =
            (*conn->async_acceptor)(NULL, conn->stream,
                                    conn->async_acceptor_baton, pool);
    }

    status = (*conn->async_handler)(NULL, conn->current_async_response,
                                    conn->async_handler_baton, pool);

    if (APR_STATUS_IS_EOF(status)) {
        serf_bucket_destroy(conn->current_async_response);
        conn->current_async_response = NULL;
        status = APR_SUCCESS;
    }

    return status;
}