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
struct st_h2o_http1_finalostream_t {int /*<<< orphan*/  chunked_buf; } ;
struct TYPE_5__ {int /*<<< orphan*/  headers; } ;
struct TYPE_6__ {int /*<<< orphan*/  pool; TYPE_1__ res; } ;
typedef  TYPE_2__ h2o_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  H2O_TOKEN_TRANSFER_ENCODING ; 
 int /*<<< orphan*/  h2o_add_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mem_alloc_pool_aligned (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ should_use_chunked_encoding (TYPE_2__*) ; 

__attribute__((used)) static void setup_chunked(struct st_h2o_http1_finalostream_t *self, h2o_req_t *req)
{
    if (should_use_chunked_encoding(req)) {
        h2o_add_header(&req->pool, &req->res.headers, H2O_TOKEN_TRANSFER_ENCODING, NULL, H2O_STRLIT("chunked"));
        self->chunked_buf = h2o_mem_alloc_pool_aligned(&req->pool, 1, sizeof(size_t) * 2 + sizeof("\r\n"));
    }
}