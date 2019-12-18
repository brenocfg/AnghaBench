#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  serf_bucket_t ;
struct TYPE_4__ {scalar_t__ state; } ;
typedef  TYPE_1__ response_context_t ;
typedef  scalar_t__ apr_status_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ STATE_BODY ; 
 scalar_t__ run_machine (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static apr_status_t wait_for_body(serf_bucket_t *bkt, response_context_t *ctx)
{
    apr_status_t status;

    /* Keep reading and moving through states if we aren't at the BODY */
    while (ctx->state != STATE_BODY) {
        status = run_machine(bkt, ctx);

        /* Anything other than APR_SUCCESS means that we cannot immediately
         * read again (for now).
         */
        if (status)
            return status;
    }
    /* in STATE_BODY */

    return APR_SUCCESS;
}