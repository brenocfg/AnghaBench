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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ crypto_hash_sha512_BYTES ; 
 int crypto_scalarmult_curve25519_BYTES ; 
 int /*<<< orphan*/  crypto_scalarmult_curve25519_base (unsigned char*,unsigned char*) ; 
 int crypto_sign_ed25519_PUBLICKEYBYTES ; 
 int crypto_sign_ed25519_SECRETKEYBYTES ; 
 scalar_t__ crypto_sign_ed25519_SEEDBYTES ; 
 int /*<<< orphan*/  crypto_sign_ed25519_keypair (unsigned char*,unsigned char*) ; 
 int crypto_sign_ed25519_pk_to_curve25519 (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_sign_ed25519_seed_keypair (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_sign_ed25519_sk_to_curve25519 (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  keypair_seed ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sodium_bin2hex (char*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  sodium_hex2bin (unsigned char*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
main(void)
{
    unsigned char ed25519_pk[crypto_sign_ed25519_PUBLICKEYBYTES];
    unsigned char ed25519_skpk[crypto_sign_ed25519_SECRETKEYBYTES];
    unsigned char curve25519_pk[crypto_scalarmult_curve25519_BYTES];
    unsigned char curve25519_pk2[crypto_scalarmult_curve25519_BYTES];
    unsigned char curve25519_sk[crypto_scalarmult_curve25519_BYTES];
    char          curve25519_pk_hex[crypto_scalarmult_curve25519_BYTES * 2 + 1];
    char          curve25519_sk_hex[crypto_scalarmult_curve25519_BYTES * 2 + 1];
    unsigned int  i;

    assert(crypto_sign_ed25519_SEEDBYTES <= crypto_hash_sha512_BYTES);
    crypto_sign_ed25519_seed_keypair(ed25519_pk, ed25519_skpk, keypair_seed);

    if (crypto_sign_ed25519_pk_to_curve25519(curve25519_pk, ed25519_pk) != 0) {
        printf("conversion failed\n");
    }
    crypto_sign_ed25519_sk_to_curve25519(curve25519_sk, ed25519_skpk);
    sodium_bin2hex(curve25519_pk_hex, sizeof curve25519_pk_hex, curve25519_pk,
                   sizeof curve25519_pk);
    sodium_bin2hex(curve25519_sk_hex, sizeof curve25519_sk_hex, curve25519_sk,
                   sizeof curve25519_sk);

    printf("curve25519 pk: [%s]\n", curve25519_pk_hex);
    printf("curve25519 sk: [%s]\n", curve25519_sk_hex);

    for (i = 0U; i < 500U; i++) {
        crypto_sign_ed25519_keypair(ed25519_pk, ed25519_skpk);
        if (crypto_sign_ed25519_pk_to_curve25519(curve25519_pk, ed25519_pk) !=
            0) {
            printf("conversion failed\n");
        }
        crypto_sign_ed25519_sk_to_curve25519(curve25519_sk, ed25519_skpk);
        crypto_scalarmult_curve25519_base(curve25519_pk2, curve25519_sk);
        if (memcmp(curve25519_pk, curve25519_pk2, sizeof curve25519_pk) != 0) {
            printf("conversion failed\n");
        }
    }

    sodium_hex2bin(ed25519_pk, crypto_sign_ed25519_PUBLICKEYBYTES,
                   "0000000000000000000000000000000000000000000000000000000000000000"
                   "0000000000000000000000000000000000000000000000000000000000000000",
                   64, NULL, NULL, NULL);
    assert(crypto_sign_ed25519_pk_to_curve25519(curve25519_pk, ed25519_pk) == -1);
    sodium_hex2bin(ed25519_pk, crypto_sign_ed25519_PUBLICKEYBYTES,
                   "0200000000000000000000000000000000000000000000000000000000000000"
                   "0000000000000000000000000000000000000000000000000000000000000000",
                   64, NULL, NULL, NULL);
    assert(crypto_sign_ed25519_pk_to_curve25519(curve25519_pk, ed25519_pk) == -1);
    sodium_hex2bin(ed25519_pk, crypto_sign_ed25519_PUBLICKEYBYTES,
                   "0500000000000000000000000000000000000000000000000000000000000000"
                   "0000000000000000000000000000000000000000000000000000000000000000",
                   64, NULL, NULL, NULL);
    assert(crypto_sign_ed25519_pk_to_curve25519(curve25519_pk, ed25519_pk) == -1);

    printf("ok\n");

    return 0;
}