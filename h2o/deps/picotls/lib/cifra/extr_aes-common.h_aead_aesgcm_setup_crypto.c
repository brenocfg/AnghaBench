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
struct TYPE_2__ {int /*<<< orphan*/ * do_decrypt; int /*<<< orphan*/ * do_encrypt_final; int /*<<< orphan*/ * do_encrypt_update; int /*<<< orphan*/ * do_encrypt_init; int /*<<< orphan*/  dispose_crypto; } ;
struct aesgcm_context_t {int /*<<< orphan*/  aes; TYPE_1__ super; } ;
typedef  int /*<<< orphan*/  ptls_aead_context_t ;

/* Variables and functions */
 int /*<<< orphan*/ * aesgcm_decrypt ; 
 int /*<<< orphan*/  aesgcm_dispose_crypto ; 
 int /*<<< orphan*/ * aesgcm_encrypt_final ; 
 int /*<<< orphan*/ * aesgcm_encrypt_init ; 
 int /*<<< orphan*/ * aesgcm_encrypt_update ; 
 int /*<<< orphan*/  cf_aes_init (int /*<<< orphan*/ *,void const*,size_t) ; 

__attribute__((used)) static inline int aead_aesgcm_setup_crypto(ptls_aead_context_t *_ctx, int is_enc, const void *key, size_t key_size)
{
    struct aesgcm_context_t *ctx = (struct aesgcm_context_t *)_ctx;

    ctx->super.dispose_crypto = aesgcm_dispose_crypto;
    if (is_enc) {
        ctx->super.do_encrypt_init = aesgcm_encrypt_init;
        ctx->super.do_encrypt_update = aesgcm_encrypt_update;
        ctx->super.do_encrypt_final = aesgcm_encrypt_final;
        ctx->super.do_decrypt = NULL;
    } else {
        ctx->super.do_encrypt_init = NULL;
        ctx->super.do_encrypt_update = NULL;
        ctx->super.do_encrypt_final = NULL;
        ctx->super.do_decrypt = aesgcm_decrypt;
    }

    cf_aes_init(&ctx->aes, key, key_size);
    return 0;
}