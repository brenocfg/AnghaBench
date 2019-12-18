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
struct TYPE_3__ {void (* do_dispose ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * do_transform; int /*<<< orphan*/ * do_init; } ;
struct TYPE_4__ {TYPE_1__ super; scalar_t__ is_enc; scalar_t__ mask_last_byte; scalar_t__ nb_right; scalar_t__ nb_left; scalar_t__ byte_length; scalar_t__ nb_rounds; int /*<<< orphan*/ * enc_ctx; } ;
typedef  TYPE_2__ ptls_ffx_context_t ;
typedef  int /*<<< orphan*/  ptls_cipher_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ptls_cipher_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ffx_dispose(ptls_cipher_context_t *_ctx)
{
    ptls_ffx_context_t *ctx = (ptls_ffx_context_t *)_ctx;

    assert(ctx->super.do_dispose == ffx_dispose);

    if (ctx->enc_ctx != NULL) {
        ptls_cipher_free(ctx->enc_ctx);
    }

    ctx->enc_ctx = NULL;
    ctx->nb_rounds = 0;
    ctx->byte_length = 0;
    ctx->nb_left = 0;
    ctx->nb_right = 0;
    ctx->mask_last_byte = 0;
    ctx->is_enc = 0;

    ctx->super.do_dispose = NULL;
    ctx->super.do_init = NULL;
    ctx->super.do_transform = NULL;
}