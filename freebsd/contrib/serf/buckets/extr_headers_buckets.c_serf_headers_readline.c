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
struct TYPE_7__ {scalar_t__ state; } ;
typedef  TYPE_2__ headers_context_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EGENERAL ; 
 int /*<<< orphan*/  APR_EOF ; 
 scalar_t__ READ_CRLF ; 
 scalar_t__ READ_DONE ; 
 scalar_t__ READ_TERM ; 
 int SERF_NEWLINE_CRLF ; 
 int SERF_NEWLINE_NONE ; 
 int /*<<< orphan*/  consume_chunk (TYPE_2__*) ; 
 int /*<<< orphan*/  select_value (TYPE_2__*,char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_status_t serf_headers_readline(serf_bucket_t *bucket,
                                          int acceptable, int *found,
                                          const char **data, apr_size_t *len)
{
    headers_context_t *ctx = bucket->data;
    apr_status_t status;

    /* ### what behavior should we use here? APR_EGENERAL for now */
    if ((acceptable & SERF_NEWLINE_CRLF) == 0)
        return APR_EGENERAL;

    /* get whatever is in this chunk */
    select_value(ctx, data, len);
    if (ctx->state == READ_DONE)
        return APR_EOF;

    /* we consumed this chunk. advance the state. */
    status = consume_chunk(ctx);

    /* the type of newline found is easy... */
    *found = (ctx->state == READ_CRLF || ctx->state == READ_TERM)
        ? SERF_NEWLINE_CRLF : SERF_NEWLINE_NONE;

    return status;
}