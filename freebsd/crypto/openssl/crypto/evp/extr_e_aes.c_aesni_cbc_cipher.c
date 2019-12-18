#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ks; } ;
struct TYPE_4__ {TYPE_1__ ks; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_AES_KEY ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_encrypting (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_iv_noconst (int /*<<< orphan*/ *) ; 
 TYPE_2__* EVP_C_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aesni_cbc_encrypt (unsigned char const*,unsigned char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aesni_cbc_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
                            const unsigned char *in, size_t len)
{
    aesni_cbc_encrypt(in, out, len, &EVP_C_DATA(EVP_AES_KEY,ctx)->ks.ks,
                      EVP_CIPHER_CTX_iv_noconst(ctx),
                      EVP_CIPHER_CTX_encrypting(ctx));

    return 1;
}