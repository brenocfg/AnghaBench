#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ secp256k1_scalar ;
typedef  int /*<<< orphan*/  secp256k1_pubkey ;
typedef  int /*<<< orphan*/  secp256k1_ge ;
typedef  int /*<<< orphan*/  secp256k1_ecdsa_signature ;
typedef  int /*<<< orphan*/  secp256k1_context ;
typedef  int /*<<< orphan*/  nonconst_ge ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  r_from_k (scalar_t__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  secp256k1_ecdsa_signature_save (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int secp256k1_ecdsa_verify (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_pubkey_save (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_add (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int secp256k1_scalar_eq (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  secp256k1_scalar_get_b32 (unsigned char*,scalar_t__*) ; 
 int /*<<< orphan*/  secp256k1_scalar_is_high (scalar_t__*) ; 
 int /*<<< orphan*/  secp256k1_scalar_mul (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_int (scalar_t__*,int) ; 

void test_exhaustive_verify(const secp256k1_context *ctx, const secp256k1_ge *group, int order) {
    int s, r, msg, key;
    for (s = 1; s < order; s++) {
        for (r = 1; r < order; r++) {
            for (msg = 1; msg < order; msg++) {
                for (key = 1; key < order; key++) {
                    secp256k1_ge nonconst_ge;
                    secp256k1_ecdsa_signature sig;
                    secp256k1_pubkey pk;
                    secp256k1_scalar sk_s, msg_s, r_s, s_s;
                    secp256k1_scalar s_times_k_s, msg_plus_r_times_sk_s;
                    int k, should_verify;
                    unsigned char msg32[32];

                    secp256k1_scalar_set_int(&s_s, s);
                    secp256k1_scalar_set_int(&r_s, r);
                    secp256k1_scalar_set_int(&msg_s, msg);
                    secp256k1_scalar_set_int(&sk_s, key);

                    /* Verify by hand */
                    /* Run through every k value that gives us this r and check that *one* works.
                     * Note there could be none, there could be multiple, ECDSA is weird. */
                    should_verify = 0;
                    for (k = 0; k < order; k++) {
                        secp256k1_scalar check_x_s;
                        r_from_k(&check_x_s, group, k);
                        if (r_s == check_x_s) {
                            secp256k1_scalar_set_int(&s_times_k_s, k);
                            secp256k1_scalar_mul(&s_times_k_s, &s_times_k_s, &s_s);
                            secp256k1_scalar_mul(&msg_plus_r_times_sk_s, &r_s, &sk_s);
                            secp256k1_scalar_add(&msg_plus_r_times_sk_s, &msg_plus_r_times_sk_s, &msg_s);
                            should_verify |= secp256k1_scalar_eq(&s_times_k_s, &msg_plus_r_times_sk_s);
                        }
                    }
                    /* nb we have a "high s" rule */
                    should_verify &= !secp256k1_scalar_is_high(&s_s);

                    /* Verify by calling verify */
                    secp256k1_ecdsa_signature_save(&sig, &r_s, &s_s);
                    memcpy(&nonconst_ge, &group[sk_s], sizeof(nonconst_ge));
                    secp256k1_pubkey_save(&pk, &nonconst_ge);
                    secp256k1_scalar_get_b32(msg32, &msg_s);
                    CHECK(should_verify ==
                          secp256k1_ecdsa_verify(ctx, &sig, msg32, &pk));
                }
            }
        }
    }
}