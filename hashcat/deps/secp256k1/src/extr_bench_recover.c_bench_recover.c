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
typedef  int /*<<< orphan*/  secp256k1_pubkey ;
typedef  int /*<<< orphan*/  secp256k1_ecdsa_recoverable_signature ;
struct TYPE_2__ {unsigned char* sig; unsigned char* msg; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ bench_recover_data ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECP256K1_EC_COMPRESSED ; 
 int /*<<< orphan*/  secp256k1_ec_pubkey_serialize (int /*<<< orphan*/ ,unsigned char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secp256k1_ecdsa_recover (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  secp256k1_ecdsa_recoverable_signature_parse_compact (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int) ; 

void bench_recover(void* arg) {
    int i;
    bench_recover_data *data = (bench_recover_data*)arg;
    secp256k1_pubkey pubkey;
    unsigned char pubkeyc[33];

    for (i = 0; i < 20000; i++) {
        int j;
        size_t pubkeylen = 33;
        secp256k1_ecdsa_recoverable_signature sig;
        CHECK(secp256k1_ecdsa_recoverable_signature_parse_compact(data->ctx, &sig, data->sig, i % 2));
        CHECK(secp256k1_ecdsa_recover(data->ctx, &pubkey, &sig, data->msg));
        CHECK(secp256k1_ec_pubkey_serialize(data->ctx, pubkeyc, &pubkeylen, &pubkey, SECP256K1_EC_COMPRESSED));
        for (j = 0; j < 32; j++) {
            data->sig[j + 32] = data->msg[j];    /* Move former message to S. */
            data->msg[j] = data->sig[j];         /* Move former R to message. */
            data->sig[j] = pubkeyc[j + 1];       /* Move recovered pubkey X coordinate to R (which must be a valid X coordinate). */
        }
    }
}