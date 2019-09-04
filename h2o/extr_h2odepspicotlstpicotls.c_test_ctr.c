#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zeroes ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {TYPE_1__* aead; } ;
typedef  TYPE_2__ ptls_cipher_suite_t ;
typedef  int /*<<< orphan*/  ptls_cipher_context_t ;
struct TYPE_8__ {size_t key_size; size_t iv_size; } ;
typedef  TYPE_3__ ptls_cipher_algorithm_t ;
struct TYPE_6__ {TYPE_3__* ctr_cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  ptls_cipher_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  ptls_cipher_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_cipher_init (int /*<<< orphan*/ *,void const*) ; 
 int /*<<< orphan*/ * ptls_cipher_new (TYPE_3__*,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void test_ctr(ptls_cipher_suite_t *cs, const uint8_t *key, size_t key_len, const void *iv, size_t iv_len,
                     const void *expected, size_t expected_len)
{
    static const uint8_t zeroes[64] = {0};

    if (cs == NULL)
        return;

    ptls_cipher_algorithm_t *algo = cs->aead->ctr_cipher;
    uint8_t buf[sizeof(zeroes)];

    assert(expected_len <= sizeof(zeroes));
    ok(algo->key_size == key_len);
    ok(algo->iv_size == iv_len);

    ptls_cipher_context_t *ctx = ptls_cipher_new(algo, 1, key);
    assert(ctx != NULL);
    ptls_cipher_init(ctx, iv);
    ptls_cipher_encrypt(ctx, buf, zeroes, expected_len);
    ptls_cipher_free(ctx);

    ok(memcmp(buf, expected, expected_len) == 0);
}