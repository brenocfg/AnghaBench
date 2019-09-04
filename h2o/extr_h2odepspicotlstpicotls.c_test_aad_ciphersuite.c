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
 size_t ptls_aead_decrypt (int /*<<< orphan*/ *,char*,char*,size_t,int,char const*,size_t) ; 
 scalar_t__ ptls_aead_encrypt_final (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ptls_aead_encrypt_init (int /*<<< orphan*/ *,int,char const*,size_t) ; 
 size_t ptls_aead_encrypt_update (int /*<<< orphan*/ *,char*,char const*,size_t) ; 
 int /*<<< orphan*/  ptls_aead_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ptls_aead_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void test_aad_ciphersuite(ptls_cipher_suite_t *cs1, ptls_cipher_suite_t *cs2)
{
    const char *traffic_secret = "012345678901234567890123456789012345678901234567", *src = "hello world", *aad = "my true aad";
    ptls_aead_context_t *c;
    char enc[256], dec[256];
    size_t enclen, declen;

    /* encrypt */
    c = ptls_aead_new(cs1->aead, cs1->hash, 1, traffic_secret, NULL);
    assert(c != NULL);
    ptls_aead_encrypt_init(c, 123, aad, strlen(aad));
    enclen = ptls_aead_encrypt_update(c, enc, src, strlen(src));
    enclen += ptls_aead_encrypt_final(c, enc + enclen);
    ptls_aead_free(c);

    /* decrypt */
    c = ptls_aead_new(cs2->aead, cs2->hash, 0, traffic_secret, NULL);
    assert(c != NULL);
    declen = ptls_aead_decrypt(c, dec, enc, enclen, 123, aad, strlen(aad));
    ok(declen == strlen(src));
    ok(memcmp(src, dec, declen) == 0);
    declen = ptls_aead_decrypt(c, dec, enc, enclen, 123, "my fake aad", strlen(aad));
    ok(declen == SIZE_MAX);
    ptls_aead_free(c);
}