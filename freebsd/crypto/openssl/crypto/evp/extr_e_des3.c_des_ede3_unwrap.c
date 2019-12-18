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
 int /*<<< orphan*/  BUF_reverse (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  CRYPTO_memcmp (unsigned char*,unsigned char*,int) ; 
 unsigned char* EVP_CIPHER_CTX_iv_noconst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,size_t) ; 
 int /*<<< orphan*/  SHA1 (unsigned char*,size_t,unsigned char*) ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  des_ede_cbc_cipher (int /*<<< orphan*/ *,unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  wrap_iv ; 

__attribute__((used)) static int des_ede3_unwrap(EVP_CIPHER_CTX *ctx, unsigned char *out,
                           const unsigned char *in, size_t inl)
{
    unsigned char icv[8], iv[8], sha1tmp[SHA_DIGEST_LENGTH];
    int rv = -1;
    if (inl < 24)
        return -1;
    if (out == NULL)
        return inl - 16;
    memcpy(EVP_CIPHER_CTX_iv_noconst(ctx), wrap_iv, 8);
    /* Decrypt first block which will end up as icv */
    des_ede_cbc_cipher(ctx, icv, in, 8);
    /* Decrypt central blocks */
    /*
     * If decrypting in place move whole output along a block so the next
     * des_ede_cbc_cipher is in place.
     */
    if (out == in) {
        memmove(out, out + 8, inl - 8);
        in -= 8;
    }
    des_ede_cbc_cipher(ctx, out, in + 8, inl - 16);
    /* Decrypt final block which will be IV */
    des_ede_cbc_cipher(ctx, iv, in + inl - 8, 8);
    /* Reverse order of everything */
    BUF_reverse(icv, NULL, 8);
    BUF_reverse(out, NULL, inl - 16);
    BUF_reverse(EVP_CIPHER_CTX_iv_noconst(ctx), iv, 8);
    /* Decrypt again using new IV */
    des_ede_cbc_cipher(ctx, out, out, inl - 16);
    des_ede_cbc_cipher(ctx, icv, icv, 8);
    /* Work out SHA1 hash of first portion */
    SHA1(out, inl - 16, sha1tmp);

    if (!CRYPTO_memcmp(sha1tmp, icv, 8))
        rv = inl - 16;
    OPENSSL_cleanse(icv, 8);
    OPENSSL_cleanse(sha1tmp, SHA_DIGEST_LENGTH);
    OPENSSL_cleanse(iv, 8);
    OPENSSL_cleanse(EVP_CIPHER_CTX_iv_noconst(ctx), 8);
    if (rv == -1)
        OPENSSL_cleanse(out, inl - 16);

    return rv;
}