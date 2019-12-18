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
typedef  int /*<<< orphan*/  u_int8_t ;
struct TYPE_4__ {int count; } ;
typedef  TYPE_1__ RMD160_CTX ;

/* Variables and functions */
 int /*<<< orphan*/ * PADDING ; 
 int /*<<< orphan*/  PUT_64BIT_LE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RMD160Update (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int RMD160_BLOCK_LENGTH ; 

void
RMD160Pad(RMD160_CTX *ctx)
{
	u_int8_t size[8];
	size_t padlen;

	PUT_64BIT_LE(size, ctx->count);

	/*
	 * pad to RMD160_BLOCK_LENGTH byte blocks, at least one byte from
	 * PADDING plus 8 bytes for the size
	 */
	padlen = RMD160_BLOCK_LENGTH - ((ctx->count / 8) % RMD160_BLOCK_LENGTH);
	if (padlen < 1 + 8)
		padlen += RMD160_BLOCK_LENGTH;
	RMD160Update(ctx, PADDING, padlen - 8);		/* padlen - 8 <= 64 */
	RMD160Update(ctx, size, 8);
}