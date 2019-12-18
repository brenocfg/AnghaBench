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
struct TYPE_8__ {scalar_t__ version; } ;
typedef  TYPE_1__ serf_status_line ;
struct TYPE_9__ {TYPE_3__* data; } ;
typedef  TYPE_2__ serf_bucket_t ;
struct TYPE_10__ {scalar_t__ state; TYPE_1__ sl; } ;
typedef  TYPE_3__ response_context_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 scalar_t__ STATE_HEADERS ; 
 scalar_t__ STATE_STATUS_LINE ; 
 int /*<<< orphan*/  run_machine (TYPE_2__*,TYPE_3__*) ; 

apr_status_t serf_bucket_response_status(
    serf_bucket_t *bkt,
    serf_status_line *sline)
{
    response_context_t *ctx = bkt->data;
    apr_status_t status;

    if (ctx->state != STATE_STATUS_LINE) {
        /* We already read it and moved on. Just return it. */
        *sline = ctx->sl;
        return APR_SUCCESS;
    }

    /* Running the state machine once will advance the machine, or state
     * that the stream isn't ready with enough data. There isn't ever a
     * need to run the machine more than once to try and satisfy this. We
     * have to look at the state to tell whether it advanced, though, as
     * it is quite possible to advance *and* to return APR_EAGAIN.
     */
    status = run_machine(bkt, ctx);
    if (ctx->state == STATE_HEADERS) {
        *sline = ctx->sl;
    }
    else {
        /* Indicate that we don't have the information yet. */
        sline->version = 0;
    }

    return status;
}