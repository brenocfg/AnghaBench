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
typedef  int /*<<< orphan*/  secp256k1_scalar ;
typedef  int /*<<< orphan*/  secp256k1_pubkey ;
typedef  int /*<<< orphan*/  secp256k1_gej ;
typedef  int /*<<< orphan*/  secp256k1_ge ;
struct TYPE_3__ {int /*<<< orphan*/  ecmult_gen_ctx; } ;
typedef  TYPE_1__ secp256k1_context ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  secp256k1_ecmult_gen (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ecmult_gen_context_is_built (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ge_set_gej (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_pubkey_save (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_b32 (int /*<<< orphan*/ *,unsigned char const*,int*) ; 

int secp256k1_ec_pubkey_create(const secp256k1_context* ctx, secp256k1_pubkey *pubkey, const unsigned char *seckey) {
    secp256k1_gej pj;
    secp256k1_ge p;
    secp256k1_scalar sec;
    int overflow;
    int ret = 0;
    VERIFY_CHECK(ctx != NULL);
    ARG_CHECK(pubkey != NULL);
    memset(pubkey, 0, sizeof(*pubkey));
    ARG_CHECK(secp256k1_ecmult_gen_context_is_built(&ctx->ecmult_gen_ctx));
    ARG_CHECK(seckey != NULL);

    secp256k1_scalar_set_b32(&sec, seckey, &overflow);
    ret = !overflow && !secp256k1_scalar_is_zero(&sec);
    if (ret) {
        secp256k1_ecmult_gen(&ctx->ecmult_gen_ctx, &pj, &sec);
        secp256k1_ge_set_gej(&p, &pj);
        secp256k1_pubkey_save(pubkey, &p);
    }
    secp256k1_scalar_clear(&sec);
    return ret;
}