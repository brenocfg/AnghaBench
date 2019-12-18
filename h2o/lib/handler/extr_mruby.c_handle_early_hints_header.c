#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  headers; } ;
struct TYPE_7__ {TYPE_1__ res; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_mruby_shared_context_t ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_3__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_add_header_by_str (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_early_hints_header(h2o_mruby_shared_context_t *shared_ctx, h2o_iovec_t *name, h2o_iovec_t value, void *_req)
{
    h2o_req_t *req = _req;
    h2o_add_header_by_str(&req->pool, &req->res.headers, name->base, name->len, 1, NULL, value.base, value.len);
    return 0;
}