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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int size; int /*<<< orphan*/ * state; } ;
typedef  TYPE_1__ blk_SHA256_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  blk_SHA256_Update (TYPE_1__*,...) ; 
 unsigned int htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_be32 (unsigned char*,int /*<<< orphan*/ ) ; 

void blk_SHA256_Final(unsigned char *digest, blk_SHA256_CTX *ctx)
{
	static const unsigned char pad[64] = { 0x80 };
	unsigned int padlen[2];
	int i;

	/* Pad with a binary 1 (ie 0x80), then zeroes, then length */
	padlen[0] = htonl((uint32_t)(ctx->size >> 29));
	padlen[1] = htonl((uint32_t)(ctx->size << 3));

	i = ctx->size & 63;
	blk_SHA256_Update(ctx, pad, 1 + (63 & (55 - i)));
	blk_SHA256_Update(ctx, padlen, 8);

	/* copy output */
	for (i = 0; i < 8; i++, digest += sizeof(uint32_t))
		put_be32(digest, ctx->state[i]);
}