#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nlast_block; unsigned char const* last_block; int /*<<< orphan*/  tbl; int /*<<< orphan*/  cctx; } ;
typedef  TYPE_1__ CMAC_CTX ;

/* Variables and functions */
 size_t EVP_CIPHER_CTX_block_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_Cipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char const*,unsigned char const*,size_t) ; 

int CMAC_Update(CMAC_CTX *ctx, const void *in, size_t dlen)
{
    const unsigned char *data = in;
    size_t bl;
    if (ctx->nlast_block == -1)
        return 0;
    if (dlen == 0)
        return 1;
    bl = EVP_CIPHER_CTX_block_size(ctx->cctx);
    /* Copy into partial block if we need to */
    if (ctx->nlast_block > 0) {
        size_t nleft;
        nleft = bl - ctx->nlast_block;
        if (dlen < nleft)
            nleft = dlen;
        memcpy(ctx->last_block + ctx->nlast_block, data, nleft);
        dlen -= nleft;
        ctx->nlast_block += nleft;
        /* If no more to process return */
        if (dlen == 0)
            return 1;
        data += nleft;
        /* Else not final block so encrypt it */
        if (!EVP_Cipher(ctx->cctx, ctx->tbl, ctx->last_block, bl))
            return 0;
    }
    /* Encrypt all but one of the complete blocks left */
    while (dlen > bl) {
        if (!EVP_Cipher(ctx->cctx, ctx->tbl, data, bl))
            return 0;
        dlen -= bl;
        data += bl;
    }
    /* Copy any data left to last block buffer */
    memcpy(ctx->last_block, data, dlen);
    ctx->nlast_block = dlen;
    return 1;

}