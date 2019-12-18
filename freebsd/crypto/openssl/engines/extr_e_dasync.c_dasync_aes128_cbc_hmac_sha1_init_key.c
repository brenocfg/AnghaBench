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
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_aes_128_cbc_hmac_sha1 () ; 
 int dasync_cipher_init_key_helper (int /*<<< orphan*/ *,unsigned char const*,unsigned char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dasync_aes128_cbc_hmac_sha1_init_key(EVP_CIPHER_CTX *ctx,
                                                const unsigned char *key,
                                                const unsigned char *iv,
                                                int enc)
{
    /*
     * We can safely assume that EVP_aes_128_cbc_hmac_sha1() != NULL,
     * see comment before the definition of dasync_aes_128_cbc_hmac_sha1().
     */
    return dasync_cipher_init_key_helper(ctx, key, iv, enc,
                                         EVP_aes_128_cbc_hmac_sha1());
}