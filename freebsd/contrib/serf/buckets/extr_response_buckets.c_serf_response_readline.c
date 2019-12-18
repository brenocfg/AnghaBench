#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* data; } ;
typedef  TYPE_1__ serf_bucket_t ;
struct TYPE_7__ {int /*<<< orphan*/  body; } ;
typedef  TYPE_2__ response_context_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 scalar_t__ serf_bucket_readline (int /*<<< orphan*/ ,int,int*,char const**,int /*<<< orphan*/ *) ; 
 scalar_t__ wait_for_body (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static apr_status_t serf_response_readline(serf_bucket_t *bucket,
                                           int acceptable, int *found,
                                           const char **data, apr_size_t *len)
{
    response_context_t *ctx = bucket->data;
    apr_status_t rv;

    rv = wait_for_body(bucket, ctx);
    if (rv) {
        return rv;
    }

    /* Delegate to the stream bucket to do the readline. */
    return serf_bucket_readline(ctx->body, acceptable, found, data, len);
}