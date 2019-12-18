#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  serf_bucket_t ;
struct TYPE_5__ {scalar_t__ state; int used; char const* line; } ;
struct TYPE_6__ {TYPE_1__ linebuf; int /*<<< orphan*/  headers; } ;
typedef  TYPE_2__ response_context_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 scalar_t__ SERF_BUCKET_READ_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERF_ERROR_BAD_HTTP_RESPONSE ; 
 scalar_t__ SERF_LINEBUF_READY ; 
 int /*<<< orphan*/  SERF_NEWLINE_ANY ; 
 int /*<<< orphan*/  apr_isspace (char const) ; 
 int /*<<< orphan*/  fetch_line (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* memchr (char const*,char,int) ; 
 int /*<<< orphan*/  serf_bucket_headers_setx (int /*<<< orphan*/ ,char const*,int,int,char const*,int,int) ; 

__attribute__((used)) static apr_status_t fetch_headers(serf_bucket_t *bkt, response_context_t *ctx)
{
    apr_status_t status;

    /* RFC 2616 says that CRLF is the only line ending, but we can easily
     * accept any kind of line ending.
     */
    status = fetch_line(ctx, SERF_NEWLINE_ANY);
    if (SERF_BUCKET_READ_ERROR(status)) {
        return status;
    }
    /* Something was read. Process it. */

    if (ctx->linebuf.state == SERF_LINEBUF_READY && ctx->linebuf.used) {
        const char *end_key;
        const char *c;

        end_key = c = memchr(ctx->linebuf.line, ':', ctx->linebuf.used);
        if (!c) {
            /* Bad headers? */
            return SERF_ERROR_BAD_HTTP_RESPONSE;
        }

        /* Skip over initial ':' */
        c++;

        /* And skip all whitespaces. */
        for(; c < ctx->linebuf.line + ctx->linebuf.used; c++)
        {
            if (!apr_isspace(*c))
            {
              break;
            }
        }

        /* Always copy the headers (from the linebuf into new mem). */
        /* ### we should be able to optimize some mem copies */
        serf_bucket_headers_setx(
            ctx->headers,
            ctx->linebuf.line, end_key - ctx->linebuf.line, 1,
            c, ctx->linebuf.line + ctx->linebuf.used - c, 1);
    }

    return status;
}