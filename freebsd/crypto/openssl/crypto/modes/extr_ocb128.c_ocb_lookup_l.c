#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t l_index; size_t max_l_index; int /*<<< orphan*/ * l; } ;
typedef  int /*<<< orphan*/  OCB_BLOCK ;
typedef  TYPE_1__ OCB128_CONTEXT ;

/* Variables and functions */
 void* OPENSSL_realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocb_double (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static OCB_BLOCK *ocb_lookup_l(OCB128_CONTEXT *ctx, size_t idx)
{
    size_t l_index = ctx->l_index;

    if (idx <= l_index) {
        return ctx->l + idx;
    }

    /* We don't have it - so calculate it */
    if (idx >= ctx->max_l_index) {
        void *tmp_ptr;
        /*
         * Each additional entry allows to process almost double as
         * much data, so that in linear world the table will need to
         * be expanded with smaller and smaller increments. Originally
         * it was doubling in size, which was a waste. Growing it
         * linearly is not formally optimal, but is simpler to implement.
         * We grow table by minimally required 4*n that would accommodate
         * the index.
         */
        ctx->max_l_index += (idx - ctx->max_l_index + 4) & ~3;
        tmp_ptr = OPENSSL_realloc(ctx->l, ctx->max_l_index * sizeof(OCB_BLOCK));
        if (tmp_ptr == NULL) /* prevent ctx->l from being clobbered */
            return NULL;
        ctx->l = tmp_ptr;
    }
    while (l_index < idx) {
        ocb_double(ctx->l + l_index, ctx->l + l_index + 1);
        l_index++;
    }
    ctx->l_index = l_index;

    return ctx->l + idx;
}