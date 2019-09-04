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
typedef  int /*<<< orphan*/  ptls_cipher_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_aes_128_ecb () ; 
 int /*<<< orphan*/  cipher_decrypt ; 
 int /*<<< orphan*/  cipher_encrypt ; 
 int cipher_setup_crypto (int /*<<< orphan*/ *,int,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aes128ecb_setup_crypto(ptls_cipher_context_t *ctx, int is_enc, const void *key)
{
    return cipher_setup_crypto(ctx, is_enc, key, EVP_aes_128_ecb(), is_enc ? cipher_encrypt : cipher_decrypt);
}