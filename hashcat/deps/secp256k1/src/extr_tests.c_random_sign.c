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
struct TYPE_2__ {int /*<<< orphan*/  ecmult_gen_ctx; } ;

/* Variables and functions */
 TYPE_1__* ctx ; 
 int /*<<< orphan*/  random_scalar_order_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ecdsa_sig_sign (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int*) ; 

void random_sign(secp256k1_scalar *sigr, secp256k1_scalar *sigs, const secp256k1_scalar *key, const secp256k1_scalar *msg, int *recid) {
    secp256k1_scalar nonce;
    do {
        random_scalar_order_test(&nonce);
    } while(!secp256k1_ecdsa_sig_sign(&ctx->ecmult_gen_ctx, sigr, sigs, key, msg, &nonce, recid));
}