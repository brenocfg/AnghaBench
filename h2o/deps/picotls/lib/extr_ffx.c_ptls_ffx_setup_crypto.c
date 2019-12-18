#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_8__ {int /*<<< orphan*/ * do_transform; int /*<<< orphan*/ * do_init; int /*<<< orphan*/  (* do_dispose ) (int /*<<< orphan*/ *) ;TYPE_1__* algo; } ;
struct TYPE_9__ {int nb_rounds; int is_enc; size_t byte_length; int nb_left; int nb_right; int mask_last_byte; TYPE_2__ super; int /*<<< orphan*/  tweaks; int /*<<< orphan*/ * enc_ctx; } ;
typedef  TYPE_3__ ptls_ffx_context_t ;
typedef  int /*<<< orphan*/  ptls_cipher_context_t ;
struct TYPE_10__ {scalar_t__ key_size; scalar_t__ iv_size; } ;
typedef  TYPE_4__ ptls_cipher_algorithm_t ;
struct TYPE_7__ {scalar_t__ key_size; scalar_t__ iv_size; size_t block_size; } ;

/* Variables and functions */
 int PTLS_ERROR_LIBRARY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ffx_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ffx_encrypt ; 
 int /*<<< orphan*/ * ffx_init ; 
 int /*<<< orphan*/ * ptls_cipher_new (TYPE_4__*,int,void const*) ; 
 int /*<<< orphan*/  ptls_clear_memory (int /*<<< orphan*/ ,int) ; 

int ptls_ffx_setup_crypto(ptls_cipher_context_t *_ctx, ptls_cipher_algorithm_t *algo, int is_enc, int nb_rounds, size_t bit_length,
                          const void *key)
{
    int ret = 0;
    ptls_ffx_context_t *ctx = (ptls_ffx_context_t *)_ctx;
    ptls_cipher_context_t *enc_ctx = NULL;
    size_t len = (bit_length + 7) / 8;
    uint8_t last_byte_mask[8] = {0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80};

    assert(len <= 32 && len >= 2);
    assert(ctx->super.do_dispose == NULL);
    assert(ctx->super.do_init == NULL);
    assert(ctx->super.do_transform == NULL);
    assert(ctx->super.algo == NULL || algo->key_size == ctx->super.algo->key_size);
    assert(ctx->super.algo == NULL || algo->iv_size == ctx->super.algo->iv_size);
    assert(ctx->super.algo == NULL || ctx->super.algo->block_size == len);
    assert(algo->iv_size == 16);

    if (len <= 32 && len >= 2) {
        /* len must be lower than 32 */
        enc_ctx = ptls_cipher_new(algo, 1, key);

        if (enc_ctx == NULL) {
            ret = PTLS_ERROR_LIBRARY;
        }
    } else {
        ret = PTLS_ERROR_LIBRARY;
    }

    if (ret == 0) {
        ctx->enc_ctx = enc_ctx;
        ctx->nb_rounds = nb_rounds;
        ctx->is_enc = is_enc;
        ctx->byte_length = len;
        ctx->nb_left = (int)len / 2;
        ctx->nb_right = (int)len - ctx->nb_left;
        ctx->mask_last_byte = last_byte_mask[bit_length % 8];
        ptls_clear_memory(ctx->tweaks, sizeof(ctx->tweaks));

        ctx->super.do_dispose = ffx_dispose;
        ctx->super.do_init = ffx_init;
        ctx->super.do_transform = ffx_encrypt;
    } else {
        ffx_dispose(_ctx);
    }

    return ret;
}