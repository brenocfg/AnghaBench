#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ecmult_gen_ctx; int /*<<< orphan*/  ecmult_ctx; } ;
typedef  TYPE_1__ secp256k1_context ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_CHECK_NO_RETURN (int) ; 
 TYPE_1__* secp256k1_context_no_precomp ; 
 int /*<<< orphan*/  secp256k1_ecmult_context_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ecmult_gen_context_clear (int /*<<< orphan*/ *) ; 

void secp256k1_context_preallocated_destroy(secp256k1_context* ctx) {
    ARG_CHECK_NO_RETURN(ctx != secp256k1_context_no_precomp);
    if (ctx != NULL) {
        secp256k1_ecmult_context_clear(&ctx->ecmult_ctx);
        secp256k1_ecmult_gen_context_clear(&ctx->ecmult_gen_ctx);
    }
}