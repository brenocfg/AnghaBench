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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {TYPE_1__* algo; } ;
struct aead_crypto_context_t {int /*<<< orphan*/  evp_ctx; TYPE_2__ super; } ;
typedef  int /*<<< orphan*/  ptls_aead_context_t ;
struct TYPE_3__ {size_t tag_size; } ;

/* Variables and functions */
 int EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CTRL_GCM_GET_TAG ; 
 int EVP_EncryptFinal_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static size_t aead_do_encrypt_final(ptls_aead_context_t *_ctx, void *_output)
{
    struct aead_crypto_context_t *ctx = (struct aead_crypto_context_t *)_ctx;
    uint8_t *output = _output;
    size_t off = 0, tag_size = ctx->super.algo->tag_size;
    int blocklen, ret;

    ret = EVP_EncryptFinal_ex(ctx->evp_ctx, output + off, &blocklen);
    assert(ret);
    off += blocklen;
    ret = EVP_CIPHER_CTX_ctrl(ctx->evp_ctx, EVP_CTRL_GCM_GET_TAG, (int)tag_size, output + off);
    assert(ret);
    off += tag_size;

    return off;
}