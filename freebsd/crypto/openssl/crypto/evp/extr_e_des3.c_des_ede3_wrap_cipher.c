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
 scalar_t__ EVP_CIPHER_CTX_encrypting (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_F_DES_EDE3_WRAP_CIPHER ; 
 size_t EVP_MAXCHUNK ; 
 int /*<<< orphan*/  EVP_R_PARTIALLY_OVERLAPPING ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int des_ede3_unwrap (int /*<<< orphan*/ *,unsigned char*,unsigned char const*,size_t) ; 
 int des_ede3_wrap (int /*<<< orphan*/ *,unsigned char*,unsigned char const*,size_t) ; 
 scalar_t__ is_partially_overlapping (unsigned char*,unsigned char const*,size_t) ; 

__attribute__((used)) static int des_ede3_wrap_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
                                const unsigned char *in, size_t inl)
{
    /*
     * Sanity check input length: we typically only wrap keys so EVP_MAXCHUNK
     * is more than will ever be needed. Also input length must be a multiple
     * of 8 bits.
     */
    if (inl >= EVP_MAXCHUNK || inl % 8)
        return -1;

    if (is_partially_overlapping(out, in, inl)) {
        EVPerr(EVP_F_DES_EDE3_WRAP_CIPHER, EVP_R_PARTIALLY_OVERLAPPING);
        return 0;
    }

    if (EVP_CIPHER_CTX_encrypting(ctx))
        return des_ede3_wrap(ctx, out, in, inl);
    else
        return des_ede3_unwrap(ctx, out, in, inl);
}