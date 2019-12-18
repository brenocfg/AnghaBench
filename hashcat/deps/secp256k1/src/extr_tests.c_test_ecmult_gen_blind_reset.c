#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  secp256k1_scalar ;
typedef  int /*<<< orphan*/  secp256k1_gej ;
struct TYPE_3__ {int /*<<< orphan*/  initial; int /*<<< orphan*/  blind; } ;
struct TYPE_4__ {TYPE_1__ ecmult_gen_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 TYPE_2__* ctx ; 
 int /*<<< orphan*/  gej_xyz_equals_gej (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ecmult_gen_blind (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secp256k1_scalar_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void test_ecmult_gen_blind_reset(void) {
    /* Test ecmult_gen() blinding reset and confirm that the blinding is consistent. */
    secp256k1_scalar b;
    secp256k1_gej initial;
    secp256k1_ecmult_gen_blind(&ctx->ecmult_gen_ctx, 0);
    b = ctx->ecmult_gen_ctx.blind;
    initial = ctx->ecmult_gen_ctx.initial;
    secp256k1_ecmult_gen_blind(&ctx->ecmult_gen_ctx, 0);
    CHECK(secp256k1_scalar_eq(&b, &ctx->ecmult_gen_ctx.blind));
    CHECK(gej_xyz_equals_gej(&initial, &ctx->ecmult_gen_ctx.initial));
}