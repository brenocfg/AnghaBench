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
 int /*<<< orphan*/  CMS_F_KEK_UNWRAP_KEY ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 size_t EVP_CIPHER_CTX_block_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DecryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DecryptUpdate (int /*<<< orphan*/ *,unsigned char*,int*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,size_t) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 

__attribute__((used)) static int kek_unwrap_key(unsigned char *out, size_t *outlen,
                          const unsigned char *in, size_t inlen,
                          EVP_CIPHER_CTX *ctx)
{
    size_t blocklen = EVP_CIPHER_CTX_block_size(ctx);
    unsigned char *tmp;
    int outl, rv = 0;
    if (inlen < 2 * blocklen) {
        /* too small */
        return 0;
    }
    if (inlen % blocklen) {
        /* Invalid size */
        return 0;
    }
    if ((tmp = OPENSSL_malloc(inlen)) == NULL) {
        CMSerr(CMS_F_KEK_UNWRAP_KEY, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    /* setup IV by decrypting last two blocks */
    if (!EVP_DecryptUpdate(ctx, tmp + inlen - 2 * blocklen, &outl,
                           in + inlen - 2 * blocklen, blocklen * 2)
        /*
         * Do a decrypt of last decrypted block to set IV to correct value
         * output it to start of buffer so we don't corrupt decrypted block
         * this works because buffer is at least two block lengths long.
         */
        || !EVP_DecryptUpdate(ctx, tmp, &outl,
                              tmp + inlen - blocklen, blocklen)
        /* Can now decrypt first n - 1 blocks */
        || !EVP_DecryptUpdate(ctx, tmp, &outl, in, inlen - blocklen)

        /* Reset IV to original value */
        || !EVP_DecryptInit_ex(ctx, NULL, NULL, NULL, NULL)
        /* Decrypt again */
        || !EVP_DecryptUpdate(ctx, tmp, &outl, tmp, inlen))
        goto err;
    /* Check check bytes */
    if (((tmp[1] ^ tmp[4]) & (tmp[2] ^ tmp[5]) & (tmp[3] ^ tmp[6])) != 0xff) {
        /* Check byte failure */
        goto err;
    }
    if (inlen < (size_t)(tmp[0] - 4)) {
        /* Invalid length value */
        goto err;
    }
    *outlen = (size_t)tmp[0];
    memcpy(out, tmp + 4, *outlen);
    rv = 1;
 err:
    OPENSSL_clear_free(tmp, inlen);
    return rv;

}