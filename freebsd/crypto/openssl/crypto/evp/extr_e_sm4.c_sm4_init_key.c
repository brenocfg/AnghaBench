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
 int /*<<< orphan*/  EVP_CIPHER_CTX_get_cipher_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SM4_set_key (unsigned char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sm4_init_key(EVP_CIPHER_CTX *ctx, const unsigned char *key,
                        const unsigned char *iv, int enc)
{
    SM4_set_key(key, EVP_CIPHER_CTX_get_cipher_data(ctx));
    return 1;
}