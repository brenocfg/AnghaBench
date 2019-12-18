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
 int /*<<< orphan*/  B ; 
 int /*<<< orphan*/  assert (int) ; 
 int crypto_scalarmult_ed25519 (unsigned char*,unsigned char*,unsigned char*) ; 
 scalar_t__ crypto_scalarmult_ed25519_BYTES ; 
 scalar_t__ crypto_scalarmult_ed25519_SCALARBYTES ; 
 int crypto_scalarmult_ed25519_base (unsigned char*,unsigned char*) ; 
 scalar_t__ crypto_scalarmult_ed25519_bytes () ; 
 scalar_t__ crypto_scalarmult_ed25519_scalarbytes () ; 
 unsigned char* max_canonical_p ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned char* non_canonical_invalid_p ; 
 unsigned char* non_canonical_p ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  randombytes_buf (unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  sodium_free (unsigned char*) ; 
 scalar_t__ sodium_malloc (scalar_t__) ; 

int
main(void)
{
    unsigned char *n, *p, *q, *q2;

    n = (unsigned char *) sodium_malloc(crypto_scalarmult_ed25519_SCALARBYTES);
    p = (unsigned char *) sodium_malloc(crypto_scalarmult_ed25519_BYTES);
    q = (unsigned char *) sodium_malloc(crypto_scalarmult_ed25519_BYTES);
    q2 = (unsigned char *) sodium_malloc(crypto_scalarmult_ed25519_BYTES);

    randombytes_buf(n, crypto_scalarmult_ed25519_SCALARBYTES);
    if (crypto_scalarmult_ed25519_base(q, n) != 0) {
        printf("crypto_scalarmult_ed25519_base() failed\n");
    }
    memcpy(p, B, crypto_scalarmult_ed25519_BYTES);
    if (crypto_scalarmult_ed25519(q2, n, p) != 0) {
        printf("crypto_scalarmult_ed25519() failed\n");
    }
    if (memcmp(q, q2, crypto_scalarmult_ed25519_BYTES) != 0) {
        printf("crypto_scalarmult_ed25519_base(n) != crypto_scalarmult_ed25519(n, 9)\n");
    }

    memset(n, 0, crypto_scalarmult_ed25519_SCALARBYTES);
    if (crypto_scalarmult_ed25519_base(q, n) != -1) {
        printf("crypto_scalarmult_ed25519_base(0) failed\n");
    }
    if (crypto_scalarmult_ed25519(q2, n, p) != -1) {
        printf("crypto_scalarmult_ed25519(0) passed\n");
    }

    n[0] = 1;
    if (crypto_scalarmult_ed25519_base(q, n) != 0) {
        printf("crypto_scalarmult_ed25519_base() failed\n");
    }
    if (crypto_scalarmult_ed25519(q2, n, p) != 0) {
        printf("crypto_scalarmult_ed25519() passed\n");
    }

    if (crypto_scalarmult_ed25519(q, n, non_canonical_p) != -1) {
        printf("crypto_scalarmult_ed25519() didn't fail\n");
    }
    if (crypto_scalarmult_ed25519(q, n, non_canonical_invalid_p) != -1) {
        printf("crypto_scalarmult_ed25519() didn't fail\n");
    }
    if (crypto_scalarmult_ed25519(q, n, max_canonical_p) != 0) {
        printf("crypto_scalarmult_ed25519() failed\n");
    }

    memset(p, 0, crypto_scalarmult_ed25519_BYTES);
    if (crypto_scalarmult_ed25519(q, n, p) != -1) {
        printf("crypto_scalarmult_ed25519() didn't fail\n");
    }
    n[0] = 8;
    if (crypto_scalarmult_ed25519(q, n, p) != -1) {
        printf("crypto_scalarmult_ed25519() didn't fail\n");
    }

    sodium_free(q2);
    sodium_free(q);
    sodium_free(p);
    sodium_free(n);

    assert(crypto_scalarmult_ed25519_BYTES == crypto_scalarmult_ed25519_bytes());
    assert(crypto_scalarmult_ed25519_SCALARBYTES == crypto_scalarmult_ed25519_scalarbytes());

    printf("OK\n");

    return 0;
}