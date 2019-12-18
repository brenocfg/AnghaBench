#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  allocator; } ;
typedef  TYPE_3__ serf_bucket_t ;
struct TYPE_13__ {int /*<<< orphan*/  used; int /*<<< orphan*/  state; } ;
struct TYPE_12__ {int code; } ;
struct TYPE_15__ {int state; int chunked; TYPE_2__ linebuf; void* body; int /*<<< orphan*/  headers; int /*<<< orphan*/  stream; TYPE_1__ sl; } ;
typedef  TYPE_4__ response_context_t ;
typedef  int /*<<< orphan*/  apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EGENERAL ; 
 int /*<<< orphan*/  APR_EOF ; 
 int /*<<< orphan*/  APR_FROM_OS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_STATUS_IS_EOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  SERF_BUCKET_READ_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERF_DEFLATE_DEFLATE ; 
 int /*<<< orphan*/  SERF_DEFLATE_GZIP ; 
 int /*<<< orphan*/  SERF_ERROR_REQUEST_LOST ; 
 int /*<<< orphan*/  SERF_LINEBUF_READY ; 
 int /*<<< orphan*/  SERF_NEWLINE_ANY ; 
#define  STATE_BODY 132 
#define  STATE_DONE 131 
#define  STATE_HEADERS 130 
#define  STATE_STATUS_LINE 129 
#define  STATE_TRAILERS 128 
 int /*<<< orphan*/  apr_strtoi64 (void const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  expect_body (TYPE_4__*) ; 
 int /*<<< orphan*/  fetch_headers (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  fetch_line (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_status_line (TYPE_4__*,int /*<<< orphan*/ ) ; 
 void* serf_bucket_barrier_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* serf_bucket_dechunk_create (void*,int /*<<< orphan*/ ) ; 
 void* serf_bucket_deflate_create (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* serf_bucket_headers_get (int /*<<< orphan*/ ,char*) ; 
 void* serf_bucket_response_body_create (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* serf_bucket_simple_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (char*,void const*) ; 

__attribute__((used)) static apr_status_t run_machine(serf_bucket_t *bkt, response_context_t *ctx)
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

        if (ctx->linebuf.state == SERF_LINEBUF_READY) {
            /* The Status-Line is in the line buffer. Process it. */
            status = parse_status_line(ctx, bkt->allocator);
            if (status)
                return status;

            /* Good times ahead: we're switching protocols! */
            if (ctx->sl.code == 101) {
                ctx->body =
                    serf_bucket_barrier_create(ctx->stream, bkt->allocator);
                ctx->state = STATE_DONE;
                break;
            }

            /* Okay... move on to reading the headers. */
            ctx->state = STATE_HEADERS;
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
        status = fetch_headers(bkt, ctx);
        if (SERF_BUCKET_READ_ERROR(status))
            return status;

        /* If an empty line was read, then we hit the end of the headers.
         * Move on to the body.
         */
        if (ctx->linebuf.state == SERF_LINEBUF_READY && !ctx->linebuf.used) {
            const void *v;

            /* Advance the state. */
            ctx->state = STATE_BODY;

            /* If this is a response to a HEAD request, or code == 1xx,204 or304
               then we don't receive a real body. */
            if (!expect_body(ctx)) {
                ctx->body = serf_bucket_simple_create(NULL, 0, NULL, NULL,
                                                      bkt->allocator);
                ctx->state = STATE_BODY;
                break;
            }

            ctx->body =
                serf_bucket_barrier_create(ctx->stream, bkt->allocator);

            /* Are we C-L, chunked, or conn close? */
            v = serf_bucket_headers_get(ctx->headers, "Content-Length");
            if (v) {
                apr_uint64_t length;
                length = apr_strtoi64(v, NULL, 10);
                if (errno == ERANGE) {
                    return APR_FROM_OS_ERROR(ERANGE);
                }
                ctx->body = serf_bucket_response_body_create(
                              ctx->body, length, bkt->allocator);
            }
            else {
                v = serf_bucket_headers_get(ctx->headers, "Transfer-Encoding");

                /* Need to handle multiple transfer-encoding. */
                if (v && strcasecmp("chunked", v) == 0) {
                    ctx->chunked = 1;
                    ctx->body = serf_bucket_dechunk_create(ctx->body,
                                                           bkt->allocator);
                }
            }
            v = serf_bucket_headers_get(ctx->headers, "Content-Encoding");
            if (v) {
                /* Need to handle multiple content-encoding. */
                if (v && strcasecmp("gzip", v) == 0) {
                    ctx->body =
                        serf_bucket_deflate_create(ctx->body, bkt->allocator,
                                                   SERF_DEFLATE_GZIP);
                }
                else if (v && strcasecmp("deflate", v) == 0) {
                    ctx->body =
                        serf_bucket_deflate_create(ctx->body, bkt->allocator,
                                                   SERF_DEFLATE_DEFLATE);
                }
            }
        }
        break;
    case STATE_BODY:
        /* Don't do anything. */
        break;
    case STATE_TRAILERS:
        status = fetch_headers(bkt, ctx);
        if (SERF_BUCKET_READ_ERROR(status))
            return status;

        /* If an empty line was read, then we're done. */
        if (ctx->linebuf.state == SERF_LINEBUF_READY && !ctx->linebuf.used) {
            ctx->state = STATE_DONE;
            return APR_EOF;
        }
        break;
    case STATE_DONE:
        return APR_EOF;
    default:
        /* Not reachable */
        return APR_EGENERAL;
    }

    return status;
}