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
struct TYPE_5__ {int has_transfer_encoding; int /*<<< orphan*/  headers; int /*<<< orphan*/  can_keepalive; } ;
struct st_h2o_mruby_http_request_context_t {TYPE_1__ req; int /*<<< orphan*/  pool; } ;
typedef  int /*<<< orphan*/  h2o_mruby_shared_context_t ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_2__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  h2o_add_header_by_str (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_lcstris (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flatten_request_header(h2o_mruby_shared_context_t *shared_ctx, h2o_iovec_t *name, h2o_iovec_t value, void *_ctx)
{
    struct st_h2o_mruby_http_request_context_t *ctx = _ctx;

    /* ignore certain headers */
    if (h2o_lcstris(name->base, name->len, H2O_STRLIT("content-length")) || h2o_lcstris(name->base, name->len, H2O_STRLIT("host")))
        return 0;

    if (h2o_lcstris(name->base, name->len, H2O_STRLIT("connection"))) {
        if (!ctx->req.can_keepalive)
            return 0;
    }

    /* mark the existence of transfer-encoding in order to prevent us from adding content-length header */
    if (h2o_lcstris(name->base, name->len, H2O_STRLIT("transfer-encoding")))
        ctx->req.has_transfer_encoding = 1;

    h2o_add_header_by_str(&ctx->pool, &ctx->req.headers, name->base, name->len, 1, NULL, value.base, value.len);

    return 0;
}