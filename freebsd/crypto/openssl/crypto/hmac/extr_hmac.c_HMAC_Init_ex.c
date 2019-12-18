#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pad ;
struct TYPE_3__ {int* key; int key_length; int /*<<< orphan*/  i_ctx; int /*<<< orphan*/  md_ctx; int /*<<< orphan*/  o_ctx; int /*<<< orphan*/  const* md; } ;
typedef  TYPE_1__ HMAC_CTX ;
typedef  int /*<<< orphan*/  const EVP_MD ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_MD_CTX_copy_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EVP_MD_FLAG_XOF ; 
 int EVP_MD_block_size (int /*<<< orphan*/  const*) ; 
 int EVP_MD_meth_get_flags (int /*<<< orphan*/  const*) ; 
 int HMAC_MAX_MD_CBLOCK_SIZE ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (int*,void const*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 

int HMAC_Init_ex(HMAC_CTX *ctx, const void *key, int len,
                 const EVP_MD *md, ENGINE *impl)
{
    int rv = 0;
    int i, j, reset = 0;
    unsigned char pad[HMAC_MAX_MD_CBLOCK_SIZE];

    /* If we are changing MD then we must have a key */
    if (md != NULL && md != ctx->md && (key == NULL || len < 0))
        return 0;

    if (md != NULL) {
        reset = 1;
        ctx->md = md;
    } else if (ctx->md) {
        md = ctx->md;
    } else {
        return 0;
    }

    /*
     * The HMAC construction is not allowed  to be used with the
     * extendable-output functions (XOF) shake128 and shake256.
     */
    if ((EVP_MD_meth_get_flags(md) & EVP_MD_FLAG_XOF) != 0)
        return 0;

    if (key != NULL) {
        reset = 1;
        j = EVP_MD_block_size(md);
        if (!ossl_assert(j <= (int)sizeof(ctx->key)))
            return 0;
        if (j < len) {
            if (!EVP_DigestInit_ex(ctx->md_ctx, md, impl)
                    || !EVP_DigestUpdate(ctx->md_ctx, key, len)
                    || !EVP_DigestFinal_ex(ctx->md_ctx, ctx->key,
                                           &ctx->key_length))
                return 0;
        } else {
            if (len < 0 || len > (int)sizeof(ctx->key))
                return 0;
            memcpy(ctx->key, key, len);
            ctx->key_length = len;
        }
        if (ctx->key_length != HMAC_MAX_MD_CBLOCK_SIZE)
            memset(&ctx->key[ctx->key_length], 0,
                   HMAC_MAX_MD_CBLOCK_SIZE - ctx->key_length);
    }

    if (reset) {
        for (i = 0; i < HMAC_MAX_MD_CBLOCK_SIZE; i++)
            pad[i] = 0x36 ^ ctx->key[i];
        if (!EVP_DigestInit_ex(ctx->i_ctx, md, impl)
                || !EVP_DigestUpdate(ctx->i_ctx, pad, EVP_MD_block_size(md)))
            goto err;

        for (i = 0; i < HMAC_MAX_MD_CBLOCK_SIZE; i++)
            pad[i] = 0x5c ^ ctx->key[i];
        if (!EVP_DigestInit_ex(ctx->o_ctx, md, impl)
                || !EVP_DigestUpdate(ctx->o_ctx, pad, EVP_MD_block_size(md)))
            goto err;
    }
    if (!EVP_MD_CTX_copy_ex(ctx->md_ctx, ctx->i_ctx))
        goto err;
    rv = 1;
 err:
    if (reset)
        OPENSSL_cleanse(pad, sizeof(pad));
    return rv;
}