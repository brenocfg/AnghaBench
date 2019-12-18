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
typedef  int uint64_t ;
struct TYPE_3__ {int* count; unsigned char const* buf; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ SHA512_CTX ;

/* Variables and functions */
 int SHA512_BLOCK_LENGTH ; 
 int /*<<< orphan*/  SHA512_Transform (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  memcpy (unsigned char const*,unsigned char const*,size_t) ; 

void
SHA512_Update(SHA512_CTX * ctx, const void *in, size_t len)
{
	uint64_t bitlen[2];
	uint64_t r;
	const unsigned char *src = in;

	/* Number of bytes left in the buffer from previous updates */
	r = (ctx->count[1] >> 3) & 0x7f;

	/* Convert the length into a number of bits */
	bitlen[1] = ((uint64_t)len) << 3;
	bitlen[0] = ((uint64_t)len) >> 61;

	/* Update number of bits */
	if ((ctx->count[1] += bitlen[1]) < bitlen[1])
		ctx->count[0]++;
	ctx->count[0] += bitlen[0];

	/* Handle the case where we don't need to perform any transforms */
	if (len < SHA512_BLOCK_LENGTH - r) {
		memcpy(&ctx->buf[r], src, len);
		return;
	}

	/* Finish the current block */
	memcpy(&ctx->buf[r], src, SHA512_BLOCK_LENGTH - r);
	SHA512_Transform(ctx->state, ctx->buf);
	src += SHA512_BLOCK_LENGTH - r;
	len -= SHA512_BLOCK_LENGTH - r;

	/* Perform complete blocks */
	while (len >= SHA512_BLOCK_LENGTH) {
		SHA512_Transform(ctx->state, src);
		src += SHA512_BLOCK_LENGTH;
		len -= SHA512_BLOCK_LENGTH;
	}

	/* Copy left over data into buffer */
	memcpy(ctx->buf, src, len);
}