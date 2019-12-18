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
 int /*<<< orphan*/  EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  EVP_CTRL_GCM_SET_TAG ; 
 int /*<<< orphan*/  EVP_DecryptFinal_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int EVP_DecryptInit_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void const*) ; 
 int EVP_DecryptUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,void const*,int) ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static size_t aead_do_decrypt(ptls_aead_context_t *_ctx, void *_output, const void *input, size_t inlen, const void *iv,
                              const void *aad, size_t aadlen)
{
    struct aead_crypto_context_t *ctx = (struct aead_crypto_context_t *)_ctx;
    uint8_t *output = _output;
    size_t off = 0, tag_size = ctx->super.algo->tag_size;
    int blocklen, ret;

    if (inlen < tag_size)
        return SIZE_MAX;

    ret = EVP_DecryptInit_ex(ctx->evp_ctx, NULL, NULL, NULL, iv);
    assert(ret);
    if (aadlen != 0) {
        ret = EVP_DecryptUpdate(ctx->evp_ctx, NULL, &blocklen, aad, (int)aadlen);
        assert(ret);
    }
    ret = EVP_DecryptUpdate(ctx->evp_ctx, output + off, &blocklen, input, (int)(inlen - tag_size));
    assert(ret);
    off += blocklen;
    if (!EVP_CIPHER_CTX_ctrl(ctx->evp_ctx, EVP_CTRL_GCM_SET_TAG, (int)tag_size, (void *)((uint8_t *)input + inlen - tag_size)))
        return SIZE_MAX;
    if (!EVP_DecryptFinal_ex(ctx->evp_ctx, output + off, &blocklen))
        return SIZE_MAX;
    off += blocklen;

    return off;
}