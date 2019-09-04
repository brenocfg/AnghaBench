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
struct chacha20poly1305_context_t {int /*<<< orphan*/  poly; int /*<<< orphan*/  textlen; int /*<<< orphan*/  aadlen; } ;
typedef  int /*<<< orphan*/  lenbuf ;

/* Variables and functions */
 int /*<<< orphan*/  cf_poly1305_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_poly1305_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  chacha20poly1305_encrypt_pad (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write64_le (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void chacha20poly1305_finalize(struct chacha20poly1305_context_t *ctx, uint8_t *tag)
{
    uint8_t lenbuf[16];

    chacha20poly1305_encrypt_pad(&ctx->poly, ctx->textlen);

    write64_le(ctx->aadlen, lenbuf);
    write64_le(ctx->textlen, lenbuf + 8);
    cf_poly1305_update(&ctx->poly, lenbuf, sizeof(lenbuf));

    cf_poly1305_finish(&ctx->poly, tag);
}