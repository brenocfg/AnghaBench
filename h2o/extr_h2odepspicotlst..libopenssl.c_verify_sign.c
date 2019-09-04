#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ ptls_iovec_t ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int EVP_DigestVerifyFinal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EVP_DigestVerifyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EVP_DigestVerifyUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_CTX_set_rsa_mgf1_md (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EVP_PKEY_CTX_set_rsa_padding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EVP_PKEY_CTX_set_rsa_pss_saltlen (int /*<<< orphan*/ *,int) ; 
 scalar_t__ EVP_PKEY_RSA ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 int PTLS_ALERT_DECRYPT_ERROR ; 
 int PTLS_ERROR_LIBRARY ; 
 int PTLS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  RSA_PKCS1_PSS_PADDING ; 

__attribute__((used)) static int verify_sign(void *verify_ctx, ptls_iovec_t data, ptls_iovec_t signature)
{
    EVP_PKEY *key = verify_ctx;
    EVP_MD_CTX *ctx = NULL;
    EVP_PKEY_CTX *pkey_ctx = NULL;
    int ret = 0;

    if (data.base == NULL)
        goto Exit;

    if ((ctx = EVP_MD_CTX_create()) == NULL) {
        ret = PTLS_ERROR_NO_MEMORY;
        goto Exit;
    }
    if (EVP_DigestVerifyInit(ctx, &pkey_ctx, EVP_sha256(), NULL, key) != 1) {
        ret = PTLS_ERROR_LIBRARY;
        goto Exit;
    }
    if (EVP_PKEY_id(key) == EVP_PKEY_RSA) {
        if (EVP_PKEY_CTX_set_rsa_padding(pkey_ctx, RSA_PKCS1_PSS_PADDING) != 1) {
            ret = PTLS_ERROR_LIBRARY;
            goto Exit;
        }
        if (EVP_PKEY_CTX_set_rsa_pss_saltlen(pkey_ctx, -1) != 1) {
            ret = PTLS_ERROR_LIBRARY;
            goto Exit;
        }
        if (EVP_PKEY_CTX_set_rsa_mgf1_md(pkey_ctx, EVP_sha256()) != 1) {
            ret = PTLS_ERROR_LIBRARY;
            goto Exit;
        }
    }
    if (EVP_DigestVerifyUpdate(ctx, data.base, data.len) != 1) {
        ret = PTLS_ERROR_LIBRARY;
        goto Exit;
    }
    if (EVP_DigestVerifyFinal(ctx, signature.base, signature.len) != 1) {
        ret = PTLS_ALERT_DECRYPT_ERROR;
        goto Exit;
    }
    ret = 0;

Exit:
    if (ctx != NULL)
        EVP_MD_CTX_destroy(ctx);
    EVP_PKEY_free(key);
    return ret;
}