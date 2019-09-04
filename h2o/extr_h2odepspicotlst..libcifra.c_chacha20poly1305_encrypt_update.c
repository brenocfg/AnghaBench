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
struct chacha20poly1305_context_t {size_t textlen; int /*<<< orphan*/  poly; int /*<<< orphan*/  chacha; } ;
typedef  int /*<<< orphan*/  ptls_aead_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  cf_chacha20_cipher (int /*<<< orphan*/ *,void const*,void*,size_t) ; 
 int /*<<< orphan*/  cf_poly1305_update (int /*<<< orphan*/ *,void*,size_t) ; 

__attribute__((used)) static size_t chacha20poly1305_encrypt_update(ptls_aead_context_t *_ctx, void *output, const void *input, size_t inlen)
{
    struct chacha20poly1305_context_t *ctx = (struct chacha20poly1305_context_t *)_ctx;

    cf_chacha20_cipher(&ctx->chacha, input, output, inlen);
    cf_poly1305_update(&ctx->poly, output, inlen);
    ctx->textlen += inlen;

    return inlen;
}