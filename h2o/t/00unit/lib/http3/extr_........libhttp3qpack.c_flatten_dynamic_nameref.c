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
struct st_h2o_qpack_flatten_context_t {scalar_t__ largest_ref; scalar_t__ base_index; TYPE_2__* headers_buf; int /*<<< orphan*/  pool; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {int len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ h2o_iovec_t ;
struct TYPE_7__ {int size; int* entries; } ;

/* Variables and functions */
 int H2O_HPACK_ENCODE_INT_MAX_LENGTH ; 
 int /*<<< orphan*/  flatten_int (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  flatten_string (TYPE_2__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ ,TYPE_2__*,int) ; 

__attribute__((used)) static void flatten_dynamic_nameref(struct st_h2o_qpack_flatten_context_t *ctx, int64_t index, h2o_iovec_t value, int dont_compress)
{
    if (index > ctx->largest_ref)
        ctx->largest_ref = index;

    h2o_vector_reserve(ctx->pool, ctx->headers_buf, ctx->headers_buf->size + H2O_HPACK_ENCODE_INT_MAX_LENGTH * 2 + value.len);
    if (index <= ctx->base_index) {
        ctx->headers_buf->entries[ctx->headers_buf->size] = 0x40 | (dont_compress ? 0x20 : 0);
        flatten_int(ctx->headers_buf, ctx->base_index - index, 4);
    } else {
        ctx->headers_buf->entries[ctx->headers_buf->size] = dont_compress ? 0x8 : 0;
        flatten_int(ctx->headers_buf, index - ctx->base_index - 1, 3);
    }
    flatten_string(ctx->headers_buf, value.base, value.len, 7, dont_compress);
}