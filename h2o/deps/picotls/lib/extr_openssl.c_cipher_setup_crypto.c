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
struct TYPE_2__ {void (* do_transform ) (int /*<<< orphan*/ *,void*,void const*,size_t) ;int /*<<< orphan*/  do_init; int /*<<< orphan*/  do_dispose; } ;
struct cipher_context_t {int /*<<< orphan*/ * evp; TYPE_1__ super; } ;
typedef  int /*<<< orphan*/  ptls_cipher_context_t ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_set_padding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_DecryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_EncryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ *) ; 
 int PTLS_ERROR_LIBRARY ; 
 int PTLS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  cipher_dispose ; 
 int /*<<< orphan*/  cipher_do_init ; 

__attribute__((used)) static int cipher_setup_crypto(ptls_cipher_context_t *_ctx, int is_enc, const void *key, const EVP_CIPHER *cipher,
                               void (*do_transform)(ptls_cipher_context_t *, void *, const void *, size_t))
{
    struct cipher_context_t *ctx = (struct cipher_context_t *)_ctx;

    ctx->super.do_dispose = cipher_dispose;
    ctx->super.do_init = cipher_do_init;
    ctx->super.do_transform = do_transform;

    if ((ctx->evp = EVP_CIPHER_CTX_new()) == NULL)
        return PTLS_ERROR_NO_MEMORY;

    if (is_enc) {
        if (!EVP_EncryptInit_ex(ctx->evp, cipher, NULL, key, NULL))
            goto Error;
    } else {
        if (!EVP_DecryptInit_ex(ctx->evp, cipher, NULL, key, NULL))
            goto Error;
        EVP_CIPHER_CTX_set_padding(ctx->evp, 0); /* required to disable one block buffering in ECB mode */
    }

    return 0;
Error:
    EVP_CIPHER_CTX_free(ctx->evp);
    return PTLS_ERROR_LIBRARY;
}