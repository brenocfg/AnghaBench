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
typedef  int /*<<< orphan*/  crypto_sign_state ;
struct TYPE_2__ {unsigned char* sk; unsigned char* pk; unsigned char* m; unsigned char* sig; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_l (unsigned char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ crypto_sign (unsigned char*,unsigned long long*,unsigned char const*,unsigned int,unsigned char*) ; 
 int crypto_sign_BYTES ; 
 int crypto_sign_PUBLICKEYBYTES ; 
 int crypto_sign_SECRETKEYBYTES ; 
 int crypto_sign_SEEDBYTES ; 
 unsigned int crypto_sign_bytes () ; 
 scalar_t__ crypto_sign_detached (unsigned char*,unsigned long long*,unsigned char const*,unsigned int,unsigned char*) ; 
 int crypto_sign_ed25519_PUBLICKEYBYTES ; 
 int crypto_sign_ed25519_SEEDBYTES ; 
 unsigned int crypto_sign_ed25519_bytes () ; 
 unsigned int crypto_sign_ed25519_messagebytes_max () ; 
 unsigned int crypto_sign_ed25519_publickeybytes () ; 
 unsigned int crypto_sign_ed25519_secretkeybytes () ; 
 unsigned int crypto_sign_ed25519_seedbytes () ; 
 int /*<<< orphan*/  crypto_sign_ed25519_sk_to_pk (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_sign_ed25519_sk_to_seed (unsigned char*,unsigned char*) ; 
 scalar_t__ crypto_sign_ed25519ph_statebytes () ; 
 int /*<<< orphan*/  crypto_sign_final_create (int /*<<< orphan*/ *,unsigned char*,unsigned long long*,unsigned char*) ; 
 int crypto_sign_final_verify (int /*<<< orphan*/ *,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_sign_init (int /*<<< orphan*/ *) ; 
 scalar_t__ crypto_sign_keypair (unsigned char*,unsigned char*) ; 
 unsigned int crypto_sign_messagebytes_max () ; 
 int crypto_sign_open (unsigned char*,unsigned long long*,unsigned char*,unsigned long long,unsigned char*) ; 
 int /*<<< orphan*/  crypto_sign_primitive () ; 
 unsigned int crypto_sign_publickeybytes () ; 
 unsigned int crypto_sign_secretkeybytes () ; 
 scalar_t__ crypto_sign_seed_keypair (unsigned char*,unsigned char*,unsigned char*) ; 
 unsigned int crypto_sign_seedbytes () ; 
 scalar_t__ crypto_sign_statebytes () ; 
 int /*<<< orphan*/  crypto_sign_update (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int crypto_sign_verify_detached (unsigned char*,unsigned char const*,unsigned int,unsigned char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 unsigned char* keypair_seed ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 unsigned char* non_canonical_p ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sodium_bin2hex (char*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  sodium_hex2bin (unsigned char*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* test_data ; 

int main(void)
{
    crypto_sign_state  st;
    unsigned char      extracted_seed[crypto_sign_ed25519_SEEDBYTES];
    unsigned char      extracted_pk[crypto_sign_ed25519_PUBLICKEYBYTES];
    unsigned char      sig[crypto_sign_BYTES];
    unsigned char      sm[1024 + crypto_sign_BYTES];
    unsigned char      m[1024];
    unsigned char      skpk[crypto_sign_SECRETKEYBYTES];
    unsigned char      pk[crypto_sign_PUBLICKEYBYTES];
    unsigned char      sk[crypto_sign_SECRETKEYBYTES];
    char               sig_hex[crypto_sign_BYTES * 2 + 1];
    char               pk_hex[crypto_sign_PUBLICKEYBYTES * 2 + 1];
    char               sk_hex[crypto_sign_SECRETKEYBYTES * 2 + 1];
    unsigned long long siglen;
    unsigned long long smlen;
    unsigned long long mlen;
    unsigned int       i;
    unsigned int       j;

    memset(sig, 0, sizeof sig);
    for (i = 0U; i < (sizeof test_data) / (sizeof test_data[0]); i++) {
#ifdef BROWSER_TESTS
        if (i % 128U != 127U) {
            continue;
        }
#endif
        memcpy(skpk, test_data[i].sk, crypto_sign_SEEDBYTES);
        memcpy(skpk + crypto_sign_SEEDBYTES, test_data[i].pk,
               crypto_sign_PUBLICKEYBYTES);
        if (crypto_sign(sm, &smlen, (const unsigned char *)test_data[i].m, i,
                        skpk) != 0) {
            printf("crypto_sign() failure: [%u]\n", i);
            continue;
        }
        if (memcmp(test_data[i].sig, sm, crypto_sign_BYTES) != 0) {
            printf("signature failure: [%u]\n", i);
            continue;
        }
        if (crypto_sign_open(m, NULL, sm, smlen, test_data[i].pk) != 0) {
            printf("crypto_sign_open() failure: [%u]\n", i);
            continue;
        }
        add_l(sm + 32);
#ifndef ED25519_COMPAT
        if (crypto_sign_open(m, &mlen, sm, smlen, test_data[i].pk) != -1) {
            printf("crypto_sign_open(): signature [%u] is malleable\n", i);
            continue;
        }
#else
        if (crypto_sign_open(m, &mlen, sm, smlen, test_data[i].pk) != 0) {
            printf("crypto_sign_open(): signature [%u] is not malleable\n", i);
            continue;
        }
#endif
        if (memcmp(test_data[i].m, m, (size_t)mlen) != 0) {
            printf("message verification failure: [%u]\n", i);
            continue;
        }
        sm[i + crypto_sign_BYTES - 1U]++;
        if (crypto_sign_open(m, &mlen, sm, smlen, test_data[i].pk) == 0) {
            printf("message can be forged: [%u]\n", i);
            continue;
        }
        if (crypto_sign_open(m, &mlen, sm, i % crypto_sign_BYTES,
                             test_data[i].pk) == 0) {
            printf("short signed message verifies: [%u]\n",
                   i % crypto_sign_BYTES);
            continue;
        }
        if (crypto_sign_detached(sig, &siglen,
                                 (const unsigned char *)test_data[i].m, i, skpk)
            != 0) {
            printf("detached signature failed: [%u]\n", i);
            continue;
        }
        if (siglen == 0U || siglen > crypto_sign_BYTES) {
            printf("detached signature has an unexpected length: [%u]\n", i);
            continue;
        }
        if (memcmp(test_data[i].sig, sig, crypto_sign_BYTES) != 0) {
            printf("detached signature failure: [%u]\n", i);
            continue;
        }
        if (crypto_sign_verify_detached(sig,
                                        (const unsigned char *)test_data[i].m,
                                        i, test_data[i].pk) != 0) {
            printf("detached signature verification failed: [%u]\n", i);
            continue;
        }
    }
    printf("%u tests\n", i);

    i--;

    memcpy(sm, test_data[i].m, i);
    if (crypto_sign(sm, &smlen, sm, i, skpk) != 0) {
        printf("crypto_sign() with overlap failed\n");
    }
    if (crypto_sign_open(sm, &mlen, sm, smlen, test_data[i].pk) != 0) {
        printf("crypto_sign_open() with overlap failed\n");
    }
    if (memcmp(test_data[i].m, sm, (size_t)mlen) != 0) {
        printf("crypto_sign_open() with overlap failed (content)\n");
    }

    for (j = 1U; j < 8U; j++) {
        sig[63] ^= (j << 5);
        if (crypto_sign_verify_detached(sig,
                                        (const unsigned char *)test_data[i].m,
                                        i, test_data[i].pk) != -1) {
            printf("detached signature verification should have failed\n");
            continue;
        }
        sig[63] ^= (j << 5);
    }

#ifndef ED25519_COMPAT
    if (crypto_sign_verify_detached(sig,
                                    (const unsigned char *)test_data[i].m,
                                    i, non_canonical_p) != -1) {
        printf("detached signature verification with non-canonical key should have failed\n");
    }
#endif
    memset(pk, 0, sizeof pk);
    if (crypto_sign_verify_detached(sig,
                                    (const unsigned char *)test_data[i].m,
                                    i, pk) != -1) {
        printf("detached signature verification should have failed\n");
    }

    memset(sig, 0xff, 32);
    sig[0] = 0xdb;
    if (crypto_sign_verify_detached(sig,
                                    (const unsigned char *)test_data[i].m,
                                    i, pk) != -1) {
        printf("detached signature verification should have failed\n");
    }
    assert(crypto_sign_detached(sig, NULL,
                                (const unsigned char *)test_data[i].m, i, skpk) == 0);

    sodium_hex2bin(pk, crypto_sign_PUBLICKEYBYTES,
                   "3eee494fb9eac773144e34b0c755affaf33ea782c0722e5ea8b150e61209ab36",
                   crypto_sign_PUBLICKEYBYTES * 2, NULL, NULL, NULL);
    if (crypto_sign_verify_detached(sig,
                                    (const unsigned char *)test_data[i].m,
                                    i, pk) != -1) {
        printf("signature with an invalid public key should have failed\n");
    }

    sodium_hex2bin(pk, crypto_sign_PUBLICKEYBYTES,
                   "0200000000000000000000000000000000000000000000000000000000000000",
                   crypto_sign_PUBLICKEYBYTES * 2, NULL, NULL, NULL);
    if (crypto_sign_verify_detached(sig,
                                    (const unsigned char *)test_data[i].m,
                                    i, pk) != -1) {
        printf("signature with an invalid public key should have failed\n");
    }

    sodium_hex2bin(pk, crypto_sign_PUBLICKEYBYTES,
                   "0500000000000000000000000000000000000000000000000000000000000000",
                   crypto_sign_PUBLICKEYBYTES * 2, NULL, NULL, NULL);
    if (crypto_sign_verify_detached(sig,
                                    (const unsigned char *)test_data[i].m,
                                    i, pk) != -1) {
        printf("signature with an invalid public key should have failed\n");
    }

    if (crypto_sign_seed_keypair(pk, sk, keypair_seed) != 0) {
        printf("crypto_sign_seed_keypair() failure\n");
        return -1;
    }
    crypto_sign_init(&st);
    crypto_sign_update(&st, (const unsigned char *)test_data[i].m, i);
    crypto_sign_final_create(&st, sig, NULL, sk);
    sodium_bin2hex(sig_hex, sizeof sig_hex, sig, sizeof sig);
    printf("ed25519ph sig: [%s]\n", sig_hex);

    crypto_sign_init(&st);
    crypto_sign_update(&st, (const unsigned char *)test_data[i].m, i);
    if (crypto_sign_final_verify(&st, sig, pk) != 0) {
        printf("ed5519ph verification failed\n");
    }
    crypto_sign_init(&st);
    crypto_sign_update(&st, (const unsigned char *)test_data[i].m, 0);
    crypto_sign_update(&st, (const unsigned char *)test_data[i].m, i / 2);
    crypto_sign_update(&st, ((const unsigned char *)test_data[i].m) + i / 2,
                       i - i / 2);
    if (crypto_sign_final_verify(&st, sig, pk) != 0) {
        printf("ed5519ph verification failed\n");
    }
    sig[0]++;
    if (crypto_sign_final_verify(&st, sig, pk) != -1) {
        printf("ed5519ph verification could be forged\n");
    }
    sig[0]--;
    pk[0]++;
    if (crypto_sign_final_verify(&st, sig, pk) != -1) {
        printf("ed5519ph verification could be forged\n");
    }
    sodium_hex2bin(sk, crypto_sign_SECRETKEYBYTES,
                   "833fe62409237b9d62ec77587520911e9a759cec1d19755b7da901b96dca3d42",
                   2 * crypto_sign_SECRETKEYBYTES , NULL, NULL, NULL);
    sodium_hex2bin(pk, crypto_sign_PUBLICKEYBYTES,
                   "ec172b93ad5e563bf4932c70e1245034c35467ef2efd4d64ebf819683467e2bf",
                   2 * crypto_sign_PUBLICKEYBYTES, NULL, NULL, NULL);
    memcpy(sk + crypto_sign_SECRETKEYBYTES - crypto_sign_PUBLICKEYBYTES,
           pk, crypto_sign_PUBLICKEYBYTES);
    crypto_sign_init(&st);
    crypto_sign_update(&st, (const unsigned char *) "abc", 3);
    crypto_sign_final_create(&st, sig, &siglen, sk);
    if (siglen == 0U || siglen > crypto_sign_BYTES) {
        printf("ed25519ph signature has an unexpected length\n");
    }
    sodium_bin2hex(sig_hex, sizeof sig_hex, sig, sizeof sig);
    printf("ed25519ph tv sig: [%s]\n", sig_hex);

    crypto_sign_init(&st);
    crypto_sign_update(&st, (const unsigned char *) "abc", 3);
    if (crypto_sign_final_verify(&st, sig, pk) != 0) {
        printf("ed25519ph verification failed\n");
    }
    if (crypto_sign_keypair(pk, sk) != 0) {
        printf("crypto_sign_keypair() failure\n");
    }
    if (crypto_sign_seed_keypair(pk, sk, keypair_seed) != 0) {
        printf("crypto_sign_seed_keypair() failure\n");
        return -1;
    }
    crypto_sign_ed25519_sk_to_seed(extracted_seed, sk);
    if (memcmp(extracted_seed, keypair_seed, crypto_sign_ed25519_SEEDBYTES)
        != 0) {
        printf("crypto_sign_ed25519_sk_to_seed() failure\n");
    }
    crypto_sign_ed25519_sk_to_pk(extracted_pk, sk);
    if (memcmp(extracted_pk, pk, crypto_sign_ed25519_PUBLICKEYBYTES) != 0) {
        printf("crypto_sign_ed25519_sk_to_pk() failure\n");
    }
    sodium_bin2hex(pk_hex, sizeof pk_hex, pk, sizeof pk);
    sodium_bin2hex(sk_hex, sizeof sk_hex, sk, sizeof sk);

    printf("pk: [%s]\n", pk_hex);
    printf("sk: [%s]\n", sk_hex);

    assert(crypto_sign_bytes() > 0U);
    assert(crypto_sign_seedbytes() > 0U);
    assert(crypto_sign_publickeybytes() > 0U);
    assert(crypto_sign_secretkeybytes() > 0U);
    assert(crypto_sign_messagebytes_max() > 0U);
    assert(strcmp(crypto_sign_primitive(), "ed25519") == 0);
    assert(crypto_sign_bytes() == crypto_sign_ed25519_bytes());
    assert(crypto_sign_seedbytes() == crypto_sign_ed25519_seedbytes());
    assert(crypto_sign_messagebytes_max() == crypto_sign_ed25519_messagebytes_max());
    assert(crypto_sign_publickeybytes()
           == crypto_sign_ed25519_publickeybytes());
    assert(crypto_sign_secretkeybytes()
           == crypto_sign_ed25519_secretkeybytes());
    assert(crypto_sign_statebytes() == crypto_sign_ed25519ph_statebytes());

#ifdef ED25519_NONDETERMINISTIC
    exit(0);
#endif

    return 0;
}