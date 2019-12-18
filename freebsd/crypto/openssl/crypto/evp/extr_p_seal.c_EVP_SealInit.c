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
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 scalar_t__ EVP_CIPHER_CTX_iv_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_key_length (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_CIPHER_CTX_rand_key (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_EncryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned char*,unsigned char*) ; 
 int EVP_MAX_KEY_LENGTH ; 
 int EVP_PKEY_encrypt_old (unsigned char*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 scalar_t__ RAND_bytes (unsigned char*,scalar_t__) ; 

int EVP_SealInit(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *type,
                 unsigned char **ek, int *ekl, unsigned char *iv,
                 EVP_PKEY **pubk, int npubk)
{
    unsigned char key[EVP_MAX_KEY_LENGTH];
    int i;
    int rv = 0;

    if (type) {
        EVP_CIPHER_CTX_reset(ctx);
        if (!EVP_EncryptInit_ex(ctx, type, NULL, NULL, NULL))
            return 0;
    }
    if ((npubk <= 0) || !pubk)
        return 1;
    if (EVP_CIPHER_CTX_rand_key(ctx, key) <= 0)
        return 0;

    if (EVP_CIPHER_CTX_iv_length(ctx)
            && RAND_bytes(iv, EVP_CIPHER_CTX_iv_length(ctx)) <= 0)
        goto err;

    if (!EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv))
        goto err;

    for (i = 0; i < npubk; i++) {
        ekl[i] =
            EVP_PKEY_encrypt_old(ek[i], key, EVP_CIPHER_CTX_key_length(ctx),
                                 pubk[i]);
        if (ekl[i] <= 0) {
            rv = -1;
            goto err;
        }
    }
    rv = npubk;
err:
    OPENSSL_cleanse(key, sizeof(key));
    return rv;
}