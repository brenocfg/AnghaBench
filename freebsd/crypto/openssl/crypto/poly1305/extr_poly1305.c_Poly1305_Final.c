#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  poly1305_emit_f ;
typedef  int /*<<< orphan*/  poly1305_blocks_f ;
struct TYPE_5__ {int /*<<< orphan*/  emit; int /*<<< orphan*/  blocks; } ;
struct TYPE_6__ {size_t num; int* data; int /*<<< orphan*/  nonce; int /*<<< orphan*/  opaque; TYPE_1__ func; } ;
typedef  TYPE_2__ POLY1305 ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_cleanse (TYPE_2__*,int) ; 
 size_t POLY1305_BLOCK_SIZE ; 
 int /*<<< orphan*/  poly1305_blocks (int /*<<< orphan*/ ,int*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poly1305_emit (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 

void Poly1305_Final(POLY1305 *ctx, unsigned char mac[16])
{
#ifdef POLY1305_ASM
    poly1305_blocks_f poly1305_blocks_p = ctx->func.blocks;
    poly1305_emit_f poly1305_emit_p = ctx->func.emit;
#endif
    size_t num;

    if ((num = ctx->num)) {
        ctx->data[num++] = 1;   /* pad bit */
        while (num < POLY1305_BLOCK_SIZE)
            ctx->data[num++] = 0;
        poly1305_blocks(ctx->opaque, ctx->data, POLY1305_BLOCK_SIZE, 0);
    }

    poly1305_emit(ctx->opaque, mac, ctx->nonce);

    /* zero out the state */
    OPENSSL_cleanse(ctx, sizeof(*ctx));
}