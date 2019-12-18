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
struct TYPE_3__ {int /*<<< orphan*/  ecmult_ctx; int /*<<< orphan*/  ecmult_gen_ctx; } ;
typedef  TYPE_1__ secp256k1_context ;

/* Variables and functions */
 size_t ROUND_TO_ALIGN (int) ; 
 scalar_t__ SECP256K1_ECMULT_CONTEXT_PREALLOCATED_SIZE ; 
 scalar_t__ SECP256K1_ECMULT_GEN_CONTEXT_PREALLOCATED_SIZE ; 
 int /*<<< orphan*/  VERIFY_CHECK (int /*<<< orphan*/ ) ; 
 scalar_t__ secp256k1_ecmult_context_is_built (int /*<<< orphan*/ *) ; 
 scalar_t__ secp256k1_ecmult_gen_context_is_built (int /*<<< orphan*/ *) ; 

size_t secp256k1_context_preallocated_clone_size(const secp256k1_context* ctx) {
    size_t ret = ROUND_TO_ALIGN(sizeof(secp256k1_context));
    VERIFY_CHECK(ctx != NULL);
    if (secp256k1_ecmult_gen_context_is_built(&ctx->ecmult_gen_ctx)) {
        ret += SECP256K1_ECMULT_GEN_CONTEXT_PREALLOCATED_SIZE;
    }
    if (secp256k1_ecmult_context_is_built(&ctx->ecmult_ctx)) {
        ret += SECP256K1_ECMULT_CONTEXT_PREALLOCATED_SIZE;
    }
    return ret;
}