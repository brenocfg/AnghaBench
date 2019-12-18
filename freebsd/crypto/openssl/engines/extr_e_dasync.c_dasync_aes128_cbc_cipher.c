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
 int /*<<< orphan*/  EVP_aes_128_cbc () ; 
 int dasync_cipher_helper (int /*<<< orphan*/ *,unsigned char*,unsigned char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dasync_aes128_cbc_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
                               const unsigned char *in, size_t inl)
{
    return dasync_cipher_helper(ctx, out, in, inl, EVP_aes_128_cbc());
}