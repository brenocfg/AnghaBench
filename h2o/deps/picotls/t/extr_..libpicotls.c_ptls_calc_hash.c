#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* final ) (TYPE_1__*,void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* update ) (TYPE_1__*,void const*,size_t) ;} ;
typedef  TYPE_1__ ptls_hash_context_t ;
struct TYPE_8__ {TYPE_1__* (* create ) () ;} ;
typedef  TYPE_2__ ptls_hash_algorithm_t ;

/* Variables and functions */
 int PTLS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  PTLS_HASH_FINAL_MODE_FREE ; 
 TYPE_1__* stub1 () ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,void const*,size_t) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,void*,int /*<<< orphan*/ ) ; 

int ptls_calc_hash(ptls_hash_algorithm_t *algo, void *output, const void *src, size_t len)
{
    ptls_hash_context_t *ctx;

    if ((ctx = algo->create()) == NULL)
        return PTLS_ERROR_NO_MEMORY;
    ctx->update(ctx, src, len);
    ctx->final(ctx, output, PTLS_HASH_FINAL_MODE_FREE);
    return 0;
}