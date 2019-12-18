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
typedef  int /*<<< orphan*/  crypto_hash_sha512_state ;
typedef  int /*<<< orphan*/  crypto_hash_sha256_state ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  crypto_hash (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 size_t crypto_hash_BYTES ; 
 unsigned int crypto_hash_bytes () ; 
 int /*<<< orphan*/  crypto_hash_primitive () ; 
 int /*<<< orphan*/  crypto_hash_sha256 (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 size_t crypto_hash_sha256_BYTES ; 
 unsigned int crypto_hash_sha256_bytes () ; 
 int crypto_hash_sha256_statebytes () ; 
 unsigned int crypto_hash_sha512_bytes () ; 
 int crypto_hash_sha512_statebytes () ; 
 scalar_t__* h ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  x ; 
 int /*<<< orphan*/  x2 ; 

int
main(void)
{
    size_t i;

    crypto_hash(h, x, sizeof x - 1U);
    for (i = 0; i < crypto_hash_BYTES; ++i) {
        printf("%02x", (unsigned int) h[i]);
    }
    printf("\n");
    crypto_hash(h, x2, sizeof x2 - 1U);
    for (i = 0; i < crypto_hash_BYTES; ++i) {
        printf("%02x", (unsigned int) h[i]);
    }
    printf("\n");
    crypto_hash_sha256(h, x, sizeof x - 1U);
    for (i = 0; i < crypto_hash_sha256_BYTES; ++i) {
        printf("%02x", (unsigned int) h[i]);
    }
    printf("\n");
    crypto_hash_sha256(h, x2, sizeof x2 - 1U);
    for (i = 0; i < crypto_hash_sha256_BYTES; ++i) {
        printf("%02x", (unsigned int) h[i]);
    }
    printf("\n");

    assert(crypto_hash_bytes() > 0U);
    assert(strcmp(crypto_hash_primitive(), "sha512") == 0);
    assert(crypto_hash_sha256_bytes() > 0U);
    assert(crypto_hash_sha512_bytes() >= crypto_hash_sha256_bytes());
    assert(crypto_hash_sha512_bytes() == crypto_hash_bytes());
    assert(crypto_hash_sha256_statebytes() == sizeof(crypto_hash_sha256_state));
    assert(crypto_hash_sha512_statebytes() == sizeof(crypto_hash_sha512_state));

    return 0;
}