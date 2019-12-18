#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
struct TYPE_6__ {scalar_t__ used; char* line; } ;
struct TYPE_5__ {int /*<<< orphan*/  reason; int /*<<< orphan*/  code; int /*<<< orphan*/  version; } ;
struct TYPE_7__ {TYPE_2__ linebuf; TYPE_1__ sl; } ;
typedef  TYPE_3__ response_context_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  SERF_ERROR_BAD_HTTP_RESPONSE ; 
 int /*<<< orphan*/  SERF_HTTP_VERSION (char,char) ; 
 scalar_t__ SERF_LINEBUF_LIMIT ; 
 int apr_date_checkmask (char*,char*) ; 
 scalar_t__ apr_isspace (char) ; 
 int /*<<< orphan*/  apr_strtoi64 (char*,char**,int) ; 
 int /*<<< orphan*/  serf_bstrmemdup (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static apr_status_t parse_status_line(response_context_t *ctx,
                                      serf_bucket_alloc_t *allocator)
{
    int res;
    char *reason; /* ### stupid APR interface makes this non-const */

    /* Ensure a valid length, to avoid overflow on the final '\0' */
    if (ctx->linebuf.used >= SERF_LINEBUF_LIMIT) {
       return SERF_ERROR_BAD_HTTP_RESPONSE;
    }

    /* apr_date_checkmask assumes its arguments are valid C strings */
    ctx->linebuf.line[ctx->linebuf.used] = '\0';

    /* ctx->linebuf.line should be of form: 'HTTP/1.1 200 OK',
       but we also explicitly allow the forms 'HTTP/1.1 200' (no reason)
       and 'HTTP/1.1 401.1 Logon failed' (iis extended error codes) */
    res = apr_date_checkmask(ctx->linebuf.line, "HTTP/#.# ###*");
    if (!res) {
        /* Not an HTTP response?  Well, at least we won't understand it. */
        return SERF_ERROR_BAD_HTTP_RESPONSE;
    }

    ctx->sl.version = SERF_HTTP_VERSION(ctx->linebuf.line[5] - '0',
                                        ctx->linebuf.line[7] - '0');
    ctx->sl.code = apr_strtoi64(ctx->linebuf.line + 8, &reason, 10);

    /* Skip leading spaces for the reason string. */
    if (apr_isspace(*reason)) {
        reason++;
    }

    /* Copy the reason value out of the line buffer. */
    ctx->sl.reason = serf_bstrmemdup(allocator, reason,
                                     ctx->linebuf.used
                                     - (reason - ctx->linebuf.line));

    return APR_SUCCESS;
}