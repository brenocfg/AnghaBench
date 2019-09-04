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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  ptls_cipher_context_t ;
typedef  int /*<<< orphan*/  ptls_cipher_algorithm_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int*) ; 
 int* malloc (size_t) ; 
 scalar_t__ memcmp (int*,int const*,size_t) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  ptls_cipher_encrypt (int /*<<< orphan*/ *,int*,int const*,size_t) ; 
 int /*<<< orphan*/  ptls_cipher_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ptls_cipher_new (int /*<<< orphan*/ *,int,int const*) ; 

__attribute__((used)) static void test_ecb(ptls_cipher_algorithm_t *algo, const void *expected, size_t expected_len)
{
    static const uint8_t key[] = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,
                                  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31},
                         plaintext[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                                        0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

    uint8_t *actual = malloc(expected_len);
    assert(actual != NULL);
    /* encrypt */
    memset(actual, 0, expected_len);
    ptls_cipher_context_t *ctx = ptls_cipher_new(algo, 1, key);
    ptls_cipher_encrypt(ctx, actual, plaintext, expected_len);
    ptls_cipher_free(ctx);
    ok(memcmp(actual, expected, expected_len) == 0);

    /* decrypt */
    ctx = ptls_cipher_new(algo, 0, key);
    ptls_cipher_encrypt(ctx, actual, actual, expected_len);
    ptls_cipher_free(ctx);
    ok(memcmp(actual, plaintext, expected_len) == 0);

    free(actual);
}