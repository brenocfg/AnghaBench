#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  tag ;
struct chacha20poly1305_context_t {size_t textlen; int /*<<< orphan*/  poly; int /*<<< orphan*/  chacha; int /*<<< orphan*/  super; } ;
typedef  int /*<<< orphan*/  ptls_aead_context_t ;

/* Variables and functions */
 int PTLS_CHACHA20POLY1305_TAG_SIZE ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  cf_chacha20_cipher (int /*<<< orphan*/ *,void const*,void*,size_t) ; 
 int /*<<< orphan*/  cf_poly1305_update (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  chacha20poly1305_finalize (struct chacha20poly1305_context_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chacha20poly1305_init (int /*<<< orphan*/ *,void const*,void const*,size_t) ; 
 scalar_t__ mem_eq (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ptls_clear_memory (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static size_t chacha20poly1305_decrypt(ptls_aead_context_t *_ctx, void *output, const void *input, size_t inlen, const void *iv,
                                       const void *aad, size_t aadlen)
{
    struct chacha20poly1305_context_t *ctx = (struct chacha20poly1305_context_t *)_ctx;
    uint8_t tag[PTLS_CHACHA20POLY1305_TAG_SIZE];
    size_t ret;

    if (inlen < sizeof(tag))
        return SIZE_MAX;

    chacha20poly1305_init(&ctx->super, iv, aad, aadlen);

    cf_poly1305_update(&ctx->poly, input, inlen - sizeof(tag));
    ctx->textlen = inlen - sizeof(tag);

    chacha20poly1305_finalize(ctx, tag);
    if (mem_eq(tag, (const uint8_t *)input + inlen - sizeof(tag), sizeof(tag))) {
        cf_chacha20_cipher(&ctx->chacha, input, output, inlen - sizeof(tag));
        ret = inlen - sizeof(tag);
    } else {
        ret = SIZE_MAX;
    }

    ptls_clear_memory(tag, sizeof(tag));
    ptls_clear_memory(&ctx->poly, sizeof(ctx->poly));

    return ret;
}