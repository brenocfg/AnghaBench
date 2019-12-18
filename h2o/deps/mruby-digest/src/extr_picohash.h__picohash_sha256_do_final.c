#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int length; int curlen; unsigned char* buf; int* state; } ;
typedef  TYPE_1__ _picohash_sha256_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  _picohash_sha256_compress (TYPE_1__*,unsigned char*) ; 

__attribute__((used)) static inline void _picohash_sha256_do_final(_picohash_sha256_ctx_t *ctx, void *digest, size_t len)
{
    unsigned char *out = digest;
    size_t i;

    /* increase the length of the message */
    ctx->length += ctx->curlen * 8;

    /* append the '1' bit */
    ctx->buf[ctx->curlen++] = (unsigned char)0x80;

    /* if the length is currently above 56 bytes we append zeros
     * then compress.  Then we can fall back to padding zeros and length
     * encoding like normal.
     */
    if (ctx->curlen > 56) {
        while (ctx->curlen < 64) {
            ctx->buf[ctx->curlen++] = (unsigned char)0;
        }
        _picohash_sha256_compress(ctx, ctx->buf);
        ctx->curlen = 0;
    }

    /* pad upto 56 bytes of zeroes */
    while (ctx->curlen < 56) {
        ctx->buf[ctx->curlen++] = (unsigned char)0;
    }

    /* store length */
    for (i = 0; i != 8; ++i)
        ctx->buf[56 + i] = ctx->length >> (56 - 8 * i);
    _picohash_sha256_compress(ctx, ctx->buf);

    /* copy output */
    for (i = 0; i != len / 4; ++i) {
        out[i * 4] = ctx->state[i] >> 24;
        out[i * 4 + 1] = ctx->state[i] >> 16;
        out[i * 4 + 2] = ctx->state[i] >> 8;
        out[i * 4 + 3] = ctx->state[i];
    }
}