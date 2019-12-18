#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ecmult_ctx; int /*<<< orphan*/  ecmult_gen_ctx; } ;
typedef  TYPE_1__ secp256k1_context ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,size_t) ; 
 size_t secp256k1_context_preallocated_clone_size (TYPE_1__ const*) ; 
 int /*<<< orphan*/  secp256k1_ecmult_context_finalize_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ecmult_gen_context_finalize_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

secp256k1_context* secp256k1_context_preallocated_clone(const secp256k1_context* ctx, void* prealloc) {
    size_t prealloc_size;
    secp256k1_context* ret;
    VERIFY_CHECK(ctx != NULL);
    ARG_CHECK(prealloc != NULL);

    prealloc_size = secp256k1_context_preallocated_clone_size(ctx);
    ret = (secp256k1_context*)prealloc;
    memcpy(ret, ctx, prealloc_size);
    secp256k1_ecmult_gen_context_finalize_memcpy(&ret->ecmult_gen_ctx, &ctx->ecmult_gen_ctx);
    secp256k1_ecmult_context_finalize_memcpy(&ret->ecmult_ctx, &ctx->ecmult_ctx);
    return ret;
}