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
 int /*<<< orphan*/  DES_ede3_cfb_encrypt (unsigned char*,unsigned char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_encrypting (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_CIPHER_CTX_iv_noconst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_test_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPH_FLAG_LENGTH_BITS ; 
 TYPE_1__* data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int des_ede3_cfb1_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
                                const unsigned char *in, size_t inl)
{
    size_t n;
    unsigned char c[1], d[1];

    if (!EVP_CIPHER_CTX_test_flags(ctx, EVP_CIPH_FLAG_LENGTH_BITS))
            inl *= 8;
    for (n = 0; n < inl; ++n) {
        c[0] = (in[n / 8] & (1 << (7 - n % 8))) ? 0x80 : 0;
        DES_ede3_cfb_encrypt(c, d, 1, 1,
                             &data(ctx)->ks1, &data(ctx)->ks2,
                             &data(ctx)->ks3,
                             (DES_cblock *)EVP_CIPHER_CTX_iv_noconst(ctx),
                             EVP_CIPHER_CTX_encrypting(ctx));
        out[n / 8] = (out[n / 8] & ~(0x80 >> (unsigned int)(n % 8)))
            | ((d[0] & 0x80) >> (unsigned int)(n % 8));
    }

    return 1;
}