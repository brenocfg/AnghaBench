#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* md_data; } ;
struct TYPE_4__ {size_t block_size; size_t num; unsigned char const* buf; int /*<<< orphan*/  A; } ;
typedef  TYPE_1__ KECCAK1600_CTX ;
typedef  TYPE_2__ EVP_MD_CTX ;

/* Variables and functions */
 size_t SHA3_absorb (int /*<<< orphan*/ ,unsigned char const*,size_t,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char const*,unsigned char const*,size_t) ; 

__attribute__((used)) static int sha3_update(EVP_MD_CTX *evp_ctx, const void *_inp, size_t len)
{
    KECCAK1600_CTX *ctx = evp_ctx->md_data;
    const unsigned char *inp = _inp;
    size_t bsz = ctx->block_size;
    size_t num, rem;

    if (len == 0)
        return 1;

    if ((num = ctx->num) != 0) {      /* process intermediate buffer? */
        rem = bsz - num;

        if (len < rem) {
            memcpy(ctx->buf + num, inp, len);
            ctx->num += len;
            return 1;
        }
        /*
         * We have enough data to fill or overflow the intermediate
         * buffer. So we append |rem| bytes and process the block,
         * leaving the rest for later processing...
         */
        memcpy(ctx->buf + num, inp, rem);
        inp += rem, len -= rem;
        (void)SHA3_absorb(ctx->A, ctx->buf, bsz, bsz);
        ctx->num = 0;
        /* ctx->buf is processed, ctx->num is guaranteed to be zero */
    }

    if (len >= bsz)
        rem = SHA3_absorb(ctx->A, inp, len, bsz);
    else
        rem = len;

    if (rem) {
        memcpy(ctx->buf, inp + len - rem, rem);
        ctx->num = rem;
    }

    return 1;
}