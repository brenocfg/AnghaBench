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
 int /*<<< orphan*/  add_P (unsigned char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ crypto_core_ed25519_BYTES ; 
 scalar_t__ crypto_core_ed25519_UNIFORMBYTES ; 
 int crypto_core_ed25519_add (unsigned char*,unsigned char*,unsigned char*) ; 
 scalar_t__ crypto_core_ed25519_bytes () ; 
 scalar_t__ crypto_core_ed25519_from_uniform (unsigned char*,unsigned char*) ; 
 int crypto_core_ed25519_is_valid_point (unsigned char*) ; 
 int crypto_core_ed25519_sub (unsigned char*,unsigned char*,unsigned char*) ; 
 scalar_t__ crypto_core_ed25519_uniformbytes () ; 
 scalar_t__ crypto_scalarmult_ed25519 (unsigned char*,unsigned char*,unsigned char*) ; 
 scalar_t__ crypto_scalarmult_ed25519_SCALARBYTES ; 
 unsigned char* max_canonical_p ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned char* non_canonical_invalid_p ; 
 unsigned char* non_canonical_p ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  randombytes_buf (unsigned char*,scalar_t__) ; 
 scalar_t__ randombytes_uniform (int) ; 
 int /*<<< orphan*/  sodium_free (unsigned char*) ; 
 scalar_t__ sodium_malloc (scalar_t__) ; 

int
main(void)
{
    unsigned char *h;
    unsigned char *p, *p2, *p3;
    unsigned char *sc;
    int            i, j;

    h = (unsigned char *) sodium_malloc(crypto_core_ed25519_UNIFORMBYTES);
    p = (unsigned char *) sodium_malloc(crypto_core_ed25519_BYTES);
    for (i = 0; i < 1000; i++) {
        randombytes_buf(h, crypto_core_ed25519_UNIFORMBYTES);
        if (crypto_core_ed25519_from_uniform(p, h) != 0) {
            printf("crypto_core_ed25519_from_uniform() failed\n");
        }
        if (crypto_core_ed25519_is_valid_point(p) == 0) {
            printf("crypto_core_ed25519_from_uniform() returned an invalid point\n");
        }
    }

    p2 = (unsigned char *) sodium_malloc(crypto_core_ed25519_BYTES);
    p3 = (unsigned char *) sodium_malloc(crypto_core_ed25519_BYTES);
    randombytes_buf(h, crypto_core_ed25519_UNIFORMBYTES);
    crypto_core_ed25519_from_uniform(p2, h);

    j = 1 + (int) randombytes_uniform(100);
    memcpy(p3, p, crypto_core_ed25519_BYTES);
    for (i = 0; i < j; i++) {
        crypto_core_ed25519_add(p, p, p2);
        if (crypto_core_ed25519_is_valid_point(p) != 1) {
            printf("crypto_core_add() returned an invalid point\n");
        }
    }
    if (memcmp(p, p3, crypto_core_ed25519_BYTES) == 0) {
        printf("crypto_core_add() failed\n");
    }
    for (i = 0; i < j; i++) {
        crypto_core_ed25519_sub(p, p, p2);
    }
    if (memcmp(p, p3, crypto_core_ed25519_BYTES) != 0) {
        printf("crypto_core_add() or crypto_core_sub() failed\n");
    }
    sc = (unsigned char *) sodium_malloc(crypto_scalarmult_ed25519_SCALARBYTES);
    memset(sc, 0, crypto_scalarmult_ed25519_SCALARBYTES);
    sc[0] = 8;
    memcpy(p2, p, crypto_core_ed25519_BYTES);
    memcpy(p3, p, crypto_core_ed25519_BYTES);

    for (i = 0; i < 254; i++) {
        crypto_core_ed25519_add(p2, p2, p2);
    }
    for (i = 0; i < 8; i++) {
        crypto_core_ed25519_add(p2, p2, p);
    }
    if (crypto_scalarmult_ed25519(p3, sc, p) != 0) {
        printf("crypto_scalarmult_ed25519() failed\n");
    }
    if (memcmp(p2, p3, crypto_core_ed25519_BYTES) != 0) {
        printf("crypto_scalarmult_ed25519() is inconsistent with crypto_core_ed25519_add()\n");
    }

    assert(crypto_core_ed25519_is_valid_point(p) == 1);

    memset(p, 0, crypto_core_ed25519_BYTES);
    assert(crypto_core_ed25519_is_valid_point(p) == 0);

    p[0] = 1;
    assert(crypto_core_ed25519_is_valid_point(p) == 0);

    p[0] = 2;
    assert(crypto_core_ed25519_is_valid_point(p) == 0);

    p[0] = 9;
    assert(crypto_core_ed25519_is_valid_point(p) == 1);

    assert(crypto_core_ed25519_is_valid_point(max_canonical_p) == 1);
    assert(crypto_core_ed25519_is_valid_point(non_canonical_invalid_p) == 0);
    assert(crypto_core_ed25519_is_valid_point(non_canonical_p) == 0);

    memcpy(p2, p, crypto_core_ed25519_BYTES);
    add_P(p2);
    crypto_core_ed25519_add(p3, p2, p2);
    crypto_core_ed25519_sub(p3, p3, p2);
    assert(memcmp(p2, p, crypto_core_ed25519_BYTES) != 0);
    assert(memcmp(p3, p, crypto_core_ed25519_BYTES) == 0);

    p[0] = 2;
    assert(crypto_core_ed25519_add(p3, p2, p) == -1);
    assert(crypto_core_ed25519_add(p3, p2, non_canonical_p) == 0);
    assert(crypto_core_ed25519_add(p3, p2, non_canonical_invalid_p) == -1);
    assert(crypto_core_ed25519_add(p3, p, p3) == -1);
    assert(crypto_core_ed25519_add(p3, non_canonical_p, p3) == 0);
    assert(crypto_core_ed25519_add(p3, non_canonical_invalid_p, p3) == -1);

    assert(crypto_core_ed25519_sub(p3, p2, p) == -1);
    assert(crypto_core_ed25519_sub(p3, p2, non_canonical_p) == 0);
    assert(crypto_core_ed25519_sub(p3, p2, non_canonical_invalid_p) == -1);
    assert(crypto_core_ed25519_sub(p3, p, p3) == -1);
    assert(crypto_core_ed25519_sub(p3, non_canonical_p, p3) == 0);
    assert(crypto_core_ed25519_sub(p3, non_canonical_invalid_p, p3) == -1);

    sodium_free(sc);
    sodium_free(p3);
    sodium_free(p2);
    sodium_free(p);
    sodium_free(h);

    assert(crypto_core_ed25519_BYTES == crypto_core_ed25519_bytes());
    assert(crypto_core_ed25519_UNIFORMBYTES == crypto_core_ed25519_uniformbytes());
    assert(crypto_core_ed25519_UNIFORMBYTES >= crypto_core_ed25519_BYTES);

    printf("OK\n");

    return 0;
}