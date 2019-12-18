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
struct TYPE_3__ {int* count; int /*<<< orphan*/ * buf; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ SHA512_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  PAD ; 
 int /*<<< orphan*/  SHA512_Transform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be64enc_vect (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
SHA512_Pad(SHA512_CTX * ctx)
{
	size_t r;

	/* Figure out how many bytes we have buffered. */
	r = (ctx->count[1] >> 3) & 0x7f;

	/* Pad to 112 mod 128, transforming if we finish a block en route. */
	if (r < 112) {
		/* Pad to 112 mod 128. */
		memcpy(&ctx->buf[r], PAD, 112 - r);
	} else {
		/* Finish the current block and mix. */
		memcpy(&ctx->buf[r], PAD, 128 - r);
		SHA512_Transform(ctx->state, ctx->buf);

		/* The start of the final block is all zeroes. */
		memset(&ctx->buf[0], 0, 112);
	}

	/* Add the terminating bit-count. */
	be64enc_vect(&ctx->buf[112], ctx->count, 16);

	/* Mix in the final block. */
	SHA512_Transform(ctx->state, ctx->buf);
}