#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {scalar_t__ id; } ;
typedef  TYPE_1__ git_oid ;
struct TYPE_7__ {int size; int /*<<< orphan*/ * H; } ;
typedef  TYPE_2__ git_hash_sha1_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  git_hash_sha1_update (TYPE_2__*,...) ; 
 unsigned int htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_be32 (scalar_t__,int /*<<< orphan*/ ) ; 

int git_hash_sha1_final(git_oid *out, git_hash_sha1_ctx *ctx)
{
	static const unsigned char pad[64] = { 0x80 };
	unsigned int padlen[2];
	int i;

	/* Pad with a binary 1 (ie 0x80), then zeroes, then length */
	padlen[0] = htonl((uint32_t)(ctx->size >> 29));
	padlen[1] = htonl((uint32_t)(ctx->size << 3));

	i = ctx->size & 63;
	git_hash_sha1_update(ctx, pad, 1+ (63 & (55 - i)));
	git_hash_sha1_update(ctx, padlen, 8);

	/* Output hash */
	for (i = 0; i < 5; i++)
		put_be32(out->id + i*4, ctx->H[i]);

	return 0;
}