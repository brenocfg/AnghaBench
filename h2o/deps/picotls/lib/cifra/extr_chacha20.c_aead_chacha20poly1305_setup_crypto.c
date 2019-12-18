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
struct chacha20poly1305_context_t {int /*<<< orphan*/  key; TYPE_1__ super; } ;
typedef  int /*<<< orphan*/  ptls_aead_context_t ;

/* Variables and functions */
 int /*<<< orphan*/ * chacha20poly1305_decrypt ; 
 int /*<<< orphan*/  chacha20poly1305_dispose_crypto ; 
 int /*<<< orphan*/ * chacha20poly1305_encrypt_final ; 
 int /*<<< orphan*/ * chacha20poly1305_encrypt_update ; 
 int /*<<< orphan*/ * chacha20poly1305_init ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static int aead_chacha20poly1305_setup_crypto(ptls_aead_context_t *_ctx, int is_enc, const void *key)
{
    struct chacha20poly1305_context_t *ctx = (struct chacha20poly1305_context_t *)_ctx;

    ctx->super.dispose_crypto = chacha20poly1305_dispose_crypto;
    if (is_enc) {
        ctx->super.do_encrypt_init = chacha20poly1305_init;
        ctx->super.do_encrypt_update = chacha20poly1305_encrypt_update;
        ctx->super.do_encrypt_final = chacha20poly1305_encrypt_final;
        ctx->super.do_decrypt = NULL;
    } else {
        ctx->super.do_encrypt_init = NULL;
        ctx->super.do_encrypt_update = NULL;
        ctx->super.do_encrypt_final = NULL;
        ctx->super.do_decrypt = chacha20poly1305_decrypt;
    }

    memcpy(ctx->key, key, sizeof(ctx->key));
    return 0;
}