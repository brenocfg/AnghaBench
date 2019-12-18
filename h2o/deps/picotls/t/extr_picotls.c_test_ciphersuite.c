#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hash; int /*<<< orphan*/  aead; } ;
typedef  TYPE_1__ ptls_cipher_suite_t ;
typedef  int /*<<< orphan*/  ptls_aead_context_t ;

/* Variables and functions */
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char const*,char*,size_t) ; 
 int /*<<< orphan*/  ok (int) ; 
 size_t ptls_aead_decrypt (int /*<<< orphan*/ *,char*,char*,size_t,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ptls_aead_encrypt_final (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ptls_aead_encrypt_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t ptls_aead_encrypt_update (int /*<<< orphan*/ *,char*,char const*,size_t) ; 
 int /*<<< orphan*/  ptls_aead_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ptls_aead_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void test_ciphersuite(ptls_cipher_suite_t *cs1, ptls_cipher_suite_t *cs2)
{
    const char *traffic_secret = "012345678901234567890123456789012345678901234567", *src1 = "hello world", *src2 = "good bye, all";
    ptls_aead_context_t *c;
    char enc1[256], enc2[256], dec1[256], dec2[256];
    size_t enc1len, enc2len, dec1len, dec2len;

    /* encrypt */
    c = ptls_aead_new(cs1->aead, cs1->hash, 1, traffic_secret, NULL);
    assert(c != NULL);
    ptls_aead_encrypt_init(c, 0, NULL, 0);
    enc1len = ptls_aead_encrypt_update(c, enc1, src1, strlen(src1));
    enc1len += ptls_aead_encrypt_final(c, enc1 + enc1len);
    ptls_aead_encrypt_init(c, 1, NULL, 0);
    enc2len = ptls_aead_encrypt_update(c, enc2, src2, strlen(src2));
    enc2len += ptls_aead_encrypt_final(c, enc2 + enc2len);
    ptls_aead_free(c);

    c = ptls_aead_new(cs2->aead, cs2->hash, 0, traffic_secret, NULL);
    assert(c != NULL);

    /* decrypt and compare */
    dec1len = ptls_aead_decrypt(c, dec1, enc1, enc1len, 0, NULL, 0);
    ok(dec1len != SIZE_MAX);
    dec2len = ptls_aead_decrypt(c, dec2, enc2, enc2len, 1, NULL, 0);
    ok(dec2len != SIZE_MAX);
    ok(strlen(src1) == dec1len);
    ok(memcmp(src1, dec1, dec1len) == 0);
    ok(strlen(src2) == dec2len);
    ok(memcmp(src2, dec2, dec2len - 1) == 0);

    /* alter and decrypt to detect failure */
    enc1[0] ^= 1;
    dec1len = ptls_aead_decrypt(c, dec1, enc1, enc1len, 0, NULL, 0);
    ok(dec1len == SIZE_MAX);

    ptls_aead_free(c);
}