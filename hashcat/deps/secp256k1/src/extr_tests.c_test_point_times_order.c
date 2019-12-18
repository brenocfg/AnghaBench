#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  secp256k1_scalar ;
typedef  int /*<<< orphan*/  secp256k1_gej ;
typedef  int /*<<< orphan*/  secp256k1_ge ;
struct TYPE_2__ {int /*<<< orphan*/  ecmult_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  SECP256K1_SCALAR_CONST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ctx ; 
 int /*<<< orphan*/  ge_equals_ge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge_equals_gej (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  random_scalar_order_test (int /*<<< orphan*/ *) ; 
 scalar_t__ secp256k1_eckey_pubkey_serialize (int /*<<< orphan*/ *,unsigned char*,size_t*,int) ; 
 int /*<<< orphan*/  secp256k1_ecmult (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ge_const_g ; 
 int secp256k1_ge_is_infinity (int /*<<< orphan*/ *) ; 
 scalar_t__ secp256k1_ge_is_valid_var (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ge_set_gej (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_add_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int secp256k1_gej_is_infinity (int /*<<< orphan*/ *) ; 
 scalar_t__ secp256k1_gej_is_valid_var (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_negate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void test_point_times_order(const secp256k1_gej *point) {
    /* X * (point + G) + (order-X) * (pointer + G) = 0 */
    secp256k1_scalar x;
    secp256k1_scalar nx;
    secp256k1_scalar zero = SECP256K1_SCALAR_CONST(0, 0, 0, 0, 0, 0, 0, 0);
    secp256k1_scalar one = SECP256K1_SCALAR_CONST(0, 0, 0, 0, 0, 0, 0, 1);
    secp256k1_gej res1, res2;
    secp256k1_ge res3;
    unsigned char pub[65];
    size_t psize = 65;
    random_scalar_order_test(&x);
    secp256k1_scalar_negate(&nx, &x);
    secp256k1_ecmult(&ctx->ecmult_ctx, &res1, point, &x, &x); /* calc res1 = x * point + x * G; */
    secp256k1_ecmult(&ctx->ecmult_ctx, &res2, point, &nx, &nx); /* calc res2 = (order - x) * point + (order - x) * G; */
    secp256k1_gej_add_var(&res1, &res1, &res2, NULL);
    CHECK(secp256k1_gej_is_infinity(&res1));
    CHECK(secp256k1_gej_is_valid_var(&res1) == 0);
    secp256k1_ge_set_gej(&res3, &res1);
    CHECK(secp256k1_ge_is_infinity(&res3));
    CHECK(secp256k1_ge_is_valid_var(&res3) == 0);
    CHECK(secp256k1_eckey_pubkey_serialize(&res3, pub, &psize, 0) == 0);
    psize = 65;
    CHECK(secp256k1_eckey_pubkey_serialize(&res3, pub, &psize, 1) == 0);
    /* check zero/one edge cases */
    secp256k1_ecmult(&ctx->ecmult_ctx, &res1, point, &zero, &zero);
    secp256k1_ge_set_gej(&res3, &res1);
    CHECK(secp256k1_ge_is_infinity(&res3));
    secp256k1_ecmult(&ctx->ecmult_ctx, &res1, point, &one, &zero);
    secp256k1_ge_set_gej(&res3, &res1);
    ge_equals_gej(&res3, point);
    secp256k1_ecmult(&ctx->ecmult_ctx, &res1, point, &zero, &one);
    secp256k1_ge_set_gej(&res3, &res1);
    ge_equals_ge(&res3, &secp256k1_ge_const_g);
}