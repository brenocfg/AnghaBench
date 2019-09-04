#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ ptls_iovec_t ;
struct TYPE_7__ {int off; int /*<<< orphan*/ * base; } ;
typedef  TYPE_2__ ptls_buffer_t ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int EVP_DigestSignFinal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 
 int EVP_DigestSignInit (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EVP_DigestSignUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_CTX_set_rsa_mgf1_md (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EVP_PKEY_CTX_set_rsa_padding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EVP_PKEY_CTX_set_rsa_pss_saltlen (int /*<<< orphan*/ *,int) ; 
 scalar_t__ EVP_PKEY_RSA ; 
 scalar_t__ EVP_PKEY_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 int PTLS_ERROR_LIBRARY ; 
 int PTLS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  RSA_PKCS1_PSS_PADDING ; 
 int ptls_buffer_reserve (TYPE_2__*,size_t) ; 

__attribute__((used)) static int do_sign(EVP_PKEY *key, ptls_buffer_t *outbuf, ptls_iovec_t input, const EVP_MD *md)
{
    EVP_MD_CTX *ctx = NULL;
    EVP_PKEY_CTX *pkey_ctx;
    size_t siglen;
    int ret;

    if ((ctx = EVP_MD_CTX_create()) == NULL) {
        ret = PTLS_ERROR_NO_MEMORY;
        goto Exit;
    }
    if (EVP_DigestSignInit(ctx, &pkey_ctx, md, NULL, key) != 1) {
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
    if (EVP_DigestSignUpdate(ctx, input.base, input.len) != 1) {
        ret = PTLS_ERROR_LIBRARY;
        goto Exit;
    }
    if (EVP_DigestSignFinal(ctx, NULL, &siglen) != 1) {
        ret = PTLS_ERROR_LIBRARY;
        goto Exit;
    }
    if ((ret = ptls_buffer_reserve(outbuf, siglen)) != 0)
        goto Exit;
    if (EVP_DigestSignFinal(ctx, outbuf->base + outbuf->off, &siglen) != 1) {
        ret = PTLS_ERROR_LIBRARY;
        goto Exit;
    }
    outbuf->off += siglen;

    ret = 0;
Exit:
    if (ctx != NULL)
        EVP_MD_CTX_destroy(ctx);
    return ret;
}