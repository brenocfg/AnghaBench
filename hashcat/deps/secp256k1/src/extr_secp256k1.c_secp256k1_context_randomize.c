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
struct TYPE_3__ {int /*<<< orphan*/  ecmult_gen_ctx; } ;
typedef  TYPE_1__ secp256k1_context ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secp256k1_ecmult_gen_blind (int /*<<< orphan*/ *,unsigned char const*) ; 
 scalar_t__ secp256k1_ecmult_gen_context_is_built (int /*<<< orphan*/ *) ; 

int secp256k1_context_randomize(secp256k1_context* ctx, const unsigned char *seed32) {
    VERIFY_CHECK(ctx != NULL);
    if (secp256k1_ecmult_gen_context_is_built(&ctx->ecmult_gen_ctx)) {
        secp256k1_ecmult_gen_blind(&ctx->ecmult_gen_ctx, seed32);
    }
    return 1;
}