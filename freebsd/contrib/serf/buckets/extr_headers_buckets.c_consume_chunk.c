#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ state; TYPE_1__* cur_read; scalar_t__ amt_read; } ;
typedef  TYPE_2__ headers_context_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_4__ {struct TYPE_4__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EOF ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 scalar_t__ READ_DONE ; 
 scalar_t__ READ_HEADER ; 
 scalar_t__ READ_TERM ; 

__attribute__((used)) static apr_status_t consume_chunk(headers_context_t *ctx)
{
    /* move to the next state, resetting the amount read. */
    ++ctx->state;
    ctx->amt_read = 0;

    /* just sent the terminator and moved to DONE. signal completion. */
    if (ctx->state == READ_DONE)
        return APR_EOF;

    /* end of this header. move to the next one. */
    if (ctx->state == READ_TERM) {
        ctx->cur_read = ctx->cur_read->next;
        if (ctx->cur_read != NULL) {
            /* We've got another head to send. Reset the read state. */
            ctx->state = READ_HEADER;
        }
        /* else leave in READ_TERM */
    }

    /* there is more data which can be read immediately. */
    return APR_SUCCESS;
}