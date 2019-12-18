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
typedef  int /*<<< orphan*/  secp256k1_pubkey ;
typedef  int /*<<< orphan*/  secp256k1_ecdsa_signature ;
struct TYPE_3__ {int* msg; int* key; int siglen; int pubkeylen; int /*<<< orphan*/  ctx; int /*<<< orphan*/  ec_group; int /*<<< orphan*/  pubkey; int /*<<< orphan*/  sig; } ;
typedef  TYPE_1__ benchmark_verify_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_GROUP_new_by_curve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NID_secp256k1 ; 
 int SECP256K1_CONTEXT_SIGN ; 
 int SECP256K1_CONTEXT_VERIFY ; 
 int /*<<< orphan*/  SECP256K1_EC_COMPRESSED ; 
 int /*<<< orphan*/  benchmark_verify ; 
 int /*<<< orphan*/  benchmark_verify_openssl ; 
 int /*<<< orphan*/  run_benchmark (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  secp256k1_context_create (int) ; 
 int /*<<< orphan*/  secp256k1_context_destroy (int /*<<< orphan*/ ) ; 
 int secp256k1_ec_pubkey_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int secp256k1_ec_pubkey_serialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int secp256k1_ecdsa_sign (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int secp256k1_ecdsa_signature_serialize_der (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

int main(void) {
    int i;
    secp256k1_pubkey pubkey;
    secp256k1_ecdsa_signature sig;
    benchmark_verify_t data;

    data.ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);

    for (i = 0; i < 32; i++) {
        data.msg[i] = 1 + i;
    }
    for (i = 0; i < 32; i++) {
        data.key[i] = 33 + i;
    }
    data.siglen = 72;
    CHECK(secp256k1_ecdsa_sign(data.ctx, &sig, data.msg, data.key, NULL, NULL));
    CHECK(secp256k1_ecdsa_signature_serialize_der(data.ctx, data.sig, &data.siglen, &sig));
    CHECK(secp256k1_ec_pubkey_create(data.ctx, &pubkey, data.key));
    data.pubkeylen = 33;
    CHECK(secp256k1_ec_pubkey_serialize(data.ctx, data.pubkey, &data.pubkeylen, &pubkey, SECP256K1_EC_COMPRESSED) == 1);

    run_benchmark("ecdsa_verify", benchmark_verify, NULL, NULL, &data, 10, 20000);
#ifdef ENABLE_OPENSSL_TESTS
    data.ec_group = EC_GROUP_new_by_curve_name(NID_secp256k1);
    run_benchmark("ecdsa_verify_openssl", benchmark_verify_openssl, NULL, NULL, &data, 10, 20000);
    EC_GROUP_free(data.ec_group);
#endif

    secp256k1_context_destroy(data.ctx);
    return 0;
}