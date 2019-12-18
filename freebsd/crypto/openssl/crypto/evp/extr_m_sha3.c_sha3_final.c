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
struct TYPE_4__ {size_t block_size; size_t num; scalar_t__ md_size; int* buf; int pad; int /*<<< orphan*/  A; } ;
typedef  TYPE_1__ KECCAK1600_CTX ;
typedef  TYPE_2__ EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA3_absorb (int /*<<< orphan*/ ,int*,size_t,size_t) ; 
 int /*<<< orphan*/  SHA3_squeeze (int /*<<< orphan*/ ,unsigned char*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int sha3_final(EVP_MD_CTX *evp_ctx, unsigned char *md)
{
    KECCAK1600_CTX *ctx = evp_ctx->md_data;
    size_t bsz = ctx->block_size;
    size_t num = ctx->num;

    if (ctx->md_size == 0)
        return 1;

    /*
     * Pad the data with 10*1. Note that |num| can be |bsz - 1|
     * in which case both byte operations below are performed on
     * same byte...
     */
    memset(ctx->buf + num, 0, bsz - num);
    ctx->buf[num] = ctx->pad;
    ctx->buf[bsz - 1] |= 0x80;

    (void)SHA3_absorb(ctx->A, ctx->buf, bsz, bsz);

    SHA3_squeeze(ctx->A, md, ctx->md_size, bsz);

    return 1;
}