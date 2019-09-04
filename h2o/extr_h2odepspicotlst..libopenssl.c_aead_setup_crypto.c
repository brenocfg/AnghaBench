#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* algo; int /*<<< orphan*/ * do_decrypt; int /*<<< orphan*/ * do_encrypt_final; int /*<<< orphan*/ * do_encrypt_update; int /*<<< orphan*/ * do_encrypt_init; int /*<<< orphan*/  (* dispose_crypto ) (TYPE_2__*) ;} ;
struct aead_crypto_context_t {TYPE_2__ super; int /*<<< orphan*/ * evp_ctx; } ;
typedef  int /*<<< orphan*/  ptls_aead_context_t ;
struct TYPE_3__ {scalar_t__ iv_size; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_CTRL_GCM_SET_IVLEN ; 
 int /*<<< orphan*/  EVP_DecryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_EncryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ *) ; 
 int PTLS_ERROR_LIBRARY ; 
 int PTLS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  aead_dispose_crypto (TYPE_2__*) ; 
 int /*<<< orphan*/ * aead_do_decrypt ; 
 int /*<<< orphan*/ * aead_do_encrypt_final ; 
 int /*<<< orphan*/ * aead_do_encrypt_init ; 
 int /*<<< orphan*/ * aead_do_encrypt_update ; 

__attribute__((used)) static int aead_setup_crypto(ptls_aead_context_t *_ctx, int is_enc, const void *key, const EVP_CIPHER *cipher)
{
    struct aead_crypto_context_t *ctx = (struct aead_crypto_context_t *)_ctx;
    int ret;

    ctx->super.dispose_crypto = aead_dispose_crypto;
    if (is_enc) {
        ctx->super.do_encrypt_init = aead_do_encrypt_init;
        ctx->super.do_encrypt_update = aead_do_encrypt_update;
        ctx->super.do_encrypt_final = aead_do_encrypt_final;
        ctx->super.do_decrypt = NULL;
    } else {
        ctx->super.do_encrypt_init = NULL;
        ctx->super.do_encrypt_update = NULL;
        ctx->super.do_encrypt_final = NULL;
        ctx->super.do_decrypt = aead_do_decrypt;
    }
    ctx->evp_ctx = NULL;

    if ((ctx->evp_ctx = EVP_CIPHER_CTX_new()) == NULL) {
        ret = PTLS_ERROR_NO_MEMORY;
        goto Error;
    }
    if (is_enc) {
        if (!EVP_EncryptInit_ex(ctx->evp_ctx, cipher, NULL, key, NULL)) {
            ret = PTLS_ERROR_LIBRARY;
            goto Error;
        }
    } else {
        if (!EVP_DecryptInit_ex(ctx->evp_ctx, cipher, NULL, key, NULL)) {
            ret = PTLS_ERROR_LIBRARY;
            goto Error;
        }
    }
    if (!EVP_CIPHER_CTX_ctrl(ctx->evp_ctx, EVP_CTRL_GCM_SET_IVLEN, (int)ctx->super.algo->iv_size, NULL)) {
        ret = PTLS_ERROR_LIBRARY;
        goto Error;
    }

    return 0;

Error:
    aead_dispose_crypto(&ctx->super);
    return ret;
}