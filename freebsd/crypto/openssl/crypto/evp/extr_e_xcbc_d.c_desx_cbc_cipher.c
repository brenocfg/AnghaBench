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
struct TYPE_2__ {int /*<<< orphan*/  outw; int /*<<< orphan*/  inw; int /*<<< orphan*/  ks; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  DES_cblock ;

/* Variables and functions */
 int /*<<< orphan*/  DES_xcbc_encrypt (unsigned char const*,unsigned char*,long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_encrypting (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_CIPHER_CTX_iv_noconst (int /*<<< orphan*/ *) ; 
 size_t EVP_MAXCHUNK ; 
 TYPE_1__* data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int desx_cbc_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
                           const unsigned char *in, size_t inl)
{
    while (inl >= EVP_MAXCHUNK) {
        DES_xcbc_encrypt(in, out, (long)EVP_MAXCHUNK, &data(ctx)->ks,
                         (DES_cblock *)EVP_CIPHER_CTX_iv_noconst(ctx),
                         &data(ctx)->inw, &data(ctx)->outw,
                         EVP_CIPHER_CTX_encrypting(ctx));
        inl -= EVP_MAXCHUNK;
        in += EVP_MAXCHUNK;
        out += EVP_MAXCHUNK;
    }
    if (inl)
        DES_xcbc_encrypt(in, out, (long)inl, &data(ctx)->ks,
                         (DES_cblock *)EVP_CIPHER_CTX_iv_noconst(ctx),
                         &data(ctx)->inw, &data(ctx)->outw,
                         EVP_CIPHER_CTX_encrypting(ctx));
    return 1;
}