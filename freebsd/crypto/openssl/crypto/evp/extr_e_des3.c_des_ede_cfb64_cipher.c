#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ks3; int /*<<< orphan*/  ks2; int /*<<< orphan*/  ks1; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  DES_cblock ;

/* Variables and functions */
 int /*<<< orphan*/  DES_ede3_cfb64_encrypt (unsigned char const*,unsigned char*,long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_encrypting (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_CIPHER_CTX_iv_noconst (int /*<<< orphan*/ *) ; 
 int EVP_CIPHER_CTX_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_set_num (int /*<<< orphan*/ *,int) ; 
 size_t EVP_MAXCHUNK ; 
 TYPE_1__* data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int des_ede_cfb64_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
                                const unsigned char *in, size_t inl)
{
    while (inl >= EVP_MAXCHUNK) {
        int num = EVP_CIPHER_CTX_num(ctx);
        DES_ede3_cfb64_encrypt(in, out, (long)EVP_MAXCHUNK,
                               &data(ctx)->ks1, &data(ctx)->ks2,
                               &data(ctx)->ks3,
                               (DES_cblock *)EVP_CIPHER_CTX_iv_noconst(ctx),
                               &num, EVP_CIPHER_CTX_encrypting(ctx));
        EVP_CIPHER_CTX_set_num(ctx, num);
        inl -= EVP_MAXCHUNK;
        in += EVP_MAXCHUNK;
        out += EVP_MAXCHUNK;
    }
    if (inl) {
        int num = EVP_CIPHER_CTX_num(ctx);
        DES_ede3_cfb64_encrypt(in, out, (long)inl,
                               &data(ctx)->ks1, &data(ctx)->ks2,
                               &data(ctx)->ks3,
                               (DES_cblock *)EVP_CIPHER_CTX_iv_noconst(ctx),
                               &num, EVP_CIPHER_CTX_encrypting(ctx));
        EVP_CIPHER_CTX_set_num(ctx, num);
    }
    return 1;
}