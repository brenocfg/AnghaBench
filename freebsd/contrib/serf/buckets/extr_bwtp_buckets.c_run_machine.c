#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  allocator; } ;
typedef  TYPE_2__ serf_bucket_t ;
struct TYPE_9__ {int /*<<< orphan*/  used; int /*<<< orphan*/  state; } ;
struct TYPE_11__ {int state; TYPE_1__ linebuf; int /*<<< orphan*/  body; int /*<<< orphan*/  type; int /*<<< orphan*/  length; int /*<<< orphan*/  stream; } ;
typedef  TYPE_3__ incoming_context_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EGENERAL ; 
 int /*<<< orphan*/  APR_EOF ; 
 int /*<<< orphan*/  APR_STATUS_IS_EOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  SERF_BUCKET_READ_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERF_ERROR_REQUEST_LOST ; 
 int /*<<< orphan*/  SERF_LINEBUF_READY ; 
 int /*<<< orphan*/  SERF_NEWLINE_ANY ; 
#define  STATE_BODY 131 
#define  STATE_DONE 130 
#define  STATE_HEADERS 129 
#define  STATE_STATUS_LINE 128 
 int /*<<< orphan*/  fetch_headers (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  fetch_line (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_status_line (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serf_bucket_barrier_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serf_bucket_limit_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static apr_status_t run_machine(serf_bucket_t *bkt, incoming_context_t *ctx)
{
    apr_status_t status = APR_SUCCESS; /* initialize to avoid gcc warnings */

    switch (ctx->state) {
    case STATE_STATUS_LINE:
        /* RFC 2616 says that CRLF is the only line ending, but we can easily
         * accept any kind of line ending.
         */
        status = fetch_line(ctx, SERF_NEWLINE_ANY);
        if (SERF_BUCKET_READ_ERROR(status))
            return status;

        if (ctx->linebuf.state == SERF_LINEBUF_READY && ctx->linebuf.used) {
            /* The Status-Line is in the line buffer. Process it. */
            status = parse_status_line(ctx, bkt->allocator);
            if (status)
                return status;

            if (ctx->length) {
                ctx->body =
                    serf_bucket_barrier_create(ctx->stream, bkt->allocator);
                ctx->body = serf_bucket_limit_create(ctx->body, ctx->length,
                                                     bkt->allocator);
                if (!ctx->type) {
                    ctx->state = STATE_HEADERS;
                } else {
                    ctx->state = STATE_BODY;
                }
            } else {
                ctx->state = STATE_DONE;
            }
        }
        else {
            /* The connection closed before we could get the next
             * response.  Treat the request as lost so that our upper
             * end knows the server never tried to give us a response.
             */
            if (APR_STATUS_IS_EOF(status)) {
                return SERF_ERROR_REQUEST_LOST;
            }
        }
        break;
    case STATE_HEADERS:
        status = fetch_headers(ctx->body, ctx);
        if (SERF_BUCKET_READ_ERROR(status))
            return status;

        /* If an empty line was read, then we hit the end of the headers.
         * Move on to the body.
         */
        if (ctx->linebuf.state == SERF_LINEBUF_READY && !ctx->linebuf.used) {
            /* Advance the state. */
            ctx->state = STATE_DONE;
        }
        break;
    case STATE_BODY:
        /* Don't do anything. */
        break;
    case STATE_DONE:
        return APR_EOF;
    default:
        /* Not reachable */
        return APR_EGENERAL;
    }

    return status;
}