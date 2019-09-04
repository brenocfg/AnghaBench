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

__attribute__((used)) static void test_bf(void)
{
#if PTLS_OPENSSL_HAVE_BF
    /* vectors from http://www.herongyang.com/Blowfish/Perl-Crypt-Blowfish-Test-Vector-128-Bit-Key.html */
    static const uint8_t key[PTLS_BLOWFISH_KEY_SIZE] = {0},
                         plaintext[PTLS_BLOWFISH_BLOCK_SIZE] = {0x4e, 0xf9, 0x97, 0x45, 0x61, 0x98, 0xdd, 0x78},
                         expected[PTLS_BLOWFISH_BLOCK_SIZE] = {0xe1, 0xc0, 0x30, 0xe7, 0x4c, 0x14, 0xd2, 0x61};
    uint8_t encrypted[PTLS_BLOWFISH_BLOCK_SIZE], decrypted[PTLS_BLOWFISH_BLOCK_SIZE];

    /* encrypt */
    ptls_cipher_context_t *ctx = ptls_cipher_new(&ptls_openssl_bfecb, 1, key);
    ptls_cipher_encrypt(ctx, encrypted, plaintext, PTLS_BLOWFISH_BLOCK_SIZE);
    ptls_cipher_free(ctx);
    ok(memcmp(encrypted, expected, PTLS_BLOWFISH_BLOCK_SIZE) == 0);

    /* decrypt */
    ctx = ptls_cipher_new(&ptls_openssl_bfecb, 0, key);
    ptls_cipher_encrypt(ctx, decrypted, "deadbeef", PTLS_BLOWFISH_BLOCK_SIZE);
    ptls_cipher_encrypt(ctx, decrypted, encrypted, PTLS_BLOWFISH_BLOCK_SIZE);
    ptls_cipher_free(ctx);
    ok(memcmp(decrypted, plaintext, PTLS_BLOWFISH_BLOCK_SIZE) == 0);
#endif
}