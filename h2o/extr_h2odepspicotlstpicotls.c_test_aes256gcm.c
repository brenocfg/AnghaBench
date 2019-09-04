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
typedef  int /*<<< orphan*/  ptls_cipher_suite_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_CIPHER_SUITE_AES_256_GCM_SHA384 ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/ * find_cipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_aad_ciphersuite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_ciphersuite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_aes256gcm(void)
{
    ptls_cipher_suite_t *cs = find_cipher(ctx, PTLS_CIPHER_SUITE_AES_256_GCM_SHA384),
                        *cs_peer = find_cipher(ctx, PTLS_CIPHER_SUITE_AES_256_GCM_SHA384);

    if (cs != NULL && cs_peer != NULL) {
        test_ciphersuite(cs, cs_peer);
        test_aad_ciphersuite(cs, cs_peer);
    }
}