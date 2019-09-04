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
typedef  int /*<<< orphan*/  tmpbuf ;
struct chacha20poly1305_context_t {size_t aadlen; scalar_t__ textlen; int /*<<< orphan*/  poly; int /*<<< orphan*/  chacha; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  ptls_aead_context_t ;

/* Variables and functions */
 int PTLS_CHACHA20POLY1305_IV_SIZE ; 
 int /*<<< orphan*/  cf_chacha20_cipher (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cf_chacha20_init_custom (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cf_poly1305_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_poly1305_update (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  chacha20poly1305_encrypt_pad (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptls_clear_memory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zeros64 ; 

__attribute__((used)) static void chacha20poly1305_init(ptls_aead_context_t *_ctx, const void *iv, const void *aad, size_t aadlen)
{
    struct chacha20poly1305_context_t *ctx = (struct chacha20poly1305_context_t *)_ctx;
    uint8_t tmpbuf[64];

    /* init chacha */
    memset(tmpbuf, 0, 16 - PTLS_CHACHA20POLY1305_IV_SIZE);
    memcpy(tmpbuf + 16 - PTLS_CHACHA20POLY1305_IV_SIZE, iv, PTLS_CHACHA20POLY1305_IV_SIZE);
    cf_chacha20_init_custom(&ctx->chacha, ctx->key, sizeof(ctx->key), tmpbuf, 4);

    /* init poly1305 (by using first 16 bytes of the key stream of the first block) */
    cf_chacha20_cipher(&ctx->chacha, zeros64, tmpbuf, 64);
    cf_poly1305_init(&ctx->poly, tmpbuf, tmpbuf + 16);

    ptls_clear_memory(tmpbuf, sizeof(tmpbuf));

    /* aad */
    if (aadlen != 0) {
        cf_poly1305_update(&ctx->poly, aad, aadlen);
        chacha20poly1305_encrypt_pad(&ctx->poly, aadlen);
    }

    ctx->aadlen = aadlen;
    ctx->textlen = 0;
}