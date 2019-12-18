#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  handler_baton; int /*<<< orphan*/  resp_bkt; scalar_t__ (* handler ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;TYPE_2__* conn; } ;
typedef  TYPE_3__ serf_request_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_8__ {TYPE_1__* ctx; } ;
struct TYPE_7__ {scalar_t__ cred_cb; } ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ serf__handle_auth_response (int*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_status_t handle_response(serf_request_t *request,
                                    apr_pool_t *pool)
{
    apr_status_t status = APR_SUCCESS;
    int consumed_response = 0;

    /* Only enable the new authentication framework if the program has
     * registered an authentication credential callback.
     *
     * This permits older Serf apps to still handle authentication
     * themselves by not registering credential callbacks.
     */
    if (request->conn->ctx->cred_cb) {
      status = serf__handle_auth_response(&consumed_response,
                                          request,
                                          request->resp_bkt,
                                          request->handler_baton,
                                          pool);

      /* If there was an error reading the response (maybe there wasn't
         enough data available), don't bother passing the response to the
         application.

         If the authentication was tried, but failed, pass the response
         to the application, maybe it can do better. */
      if (status) {
          return status;
      }
    }

    if (!consumed_response) {
        return (*request->handler)(request,
                                   request->resp_bkt,
                                   request->handler_baton,
                                   pool);
    }

    return status;
}