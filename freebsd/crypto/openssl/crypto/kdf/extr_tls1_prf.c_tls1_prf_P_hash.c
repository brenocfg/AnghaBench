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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  A1 ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestSignFinal (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 int /*<<< orphan*/  EVP_DigestSignInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestSignUpdate (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_FLAG_NON_FIPS_ALLOW ; 
 int /*<<< orphan*/  EVP_MD_CTX_copy_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_MD_CTX_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_PKEY_HMAC ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new_raw_private_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 

__attribute__((used)) static int tls1_prf_P_hash(const EVP_MD *md,
                           const unsigned char *sec, size_t sec_len,
                           const unsigned char *seed, size_t seed_len,
                           unsigned char *out, size_t olen)
{
    int chunk;
    EVP_MD_CTX *ctx = NULL, *ctx_tmp = NULL, *ctx_init = NULL;
    EVP_PKEY *mac_key = NULL;
    unsigned char A1[EVP_MAX_MD_SIZE];
    size_t A1_len;
    int ret = 0;

    chunk = EVP_MD_size(md);
    if (!ossl_assert(chunk > 0))
        goto err;

    ctx = EVP_MD_CTX_new();
    ctx_tmp = EVP_MD_CTX_new();
    ctx_init = EVP_MD_CTX_new();
    if (ctx == NULL || ctx_tmp == NULL || ctx_init == NULL)
        goto err;
    EVP_MD_CTX_set_flags(ctx_init, EVP_MD_CTX_FLAG_NON_FIPS_ALLOW);
    mac_key = EVP_PKEY_new_raw_private_key(EVP_PKEY_HMAC, NULL, sec, sec_len);
    if (mac_key == NULL)
        goto err;
    if (!EVP_DigestSignInit(ctx_init, NULL, md, NULL, mac_key))
        goto err;
    if (!EVP_MD_CTX_copy_ex(ctx, ctx_init))
        goto err;
    if (seed != NULL && !EVP_DigestSignUpdate(ctx, seed, seed_len))
        goto err;
    if (!EVP_DigestSignFinal(ctx, A1, &A1_len))
        goto err;

    for (;;) {
        /* Reinit mac contexts */
        if (!EVP_MD_CTX_copy_ex(ctx, ctx_init))
            goto err;
        if (!EVP_DigestSignUpdate(ctx, A1, A1_len))
            goto err;
        if (olen > (size_t)chunk && !EVP_MD_CTX_copy_ex(ctx_tmp, ctx))
            goto err;
        if (seed && !EVP_DigestSignUpdate(ctx, seed, seed_len))
            goto err;

        if (olen > (size_t)chunk) {
            size_t mac_len;
            if (!EVP_DigestSignFinal(ctx, out, &mac_len))
                goto err;
            out += mac_len;
            olen -= mac_len;
            /* calc the next A1 value */
            if (!EVP_DigestSignFinal(ctx_tmp, A1, &A1_len))
                goto err;
        } else {                /* last one */

            if (!EVP_DigestSignFinal(ctx, A1, &A1_len))
                goto err;
            memcpy(out, A1, olen);
            break;
        }
    }
    ret = 1;
 err:
    EVP_PKEY_free(mac_key);
    EVP_MD_CTX_free(ctx);
    EVP_MD_CTX_free(ctx_tmp);
    EVP_MD_CTX_free(ctx_init);
    OPENSSL_cleanse(A1, sizeof(A1));
    return ret;
}