#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int count; int /*<<< orphan*/ * state; } ;
typedef  TYPE_1__ RMD160_CTX ;

/* Variables and functions */
 int /*<<< orphan*/ * PADDING ; 
 int /*<<< orphan*/  PUT_32BIT_LE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_64BIT_LE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RMD160Update (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
RMD160Final(u_char digest[20], RMD160_CTX *ctx)
{
	int i;
	u_char size[8];
	u_int32_t padlen;

	PUT_64BIT_LE(size, ctx->count);

	/*
	 * pad to 64 byte blocks, at least one byte from PADDING plus 8 bytes
	 * for the size
	 */
	padlen = 64 - ((ctx->count/8) % 64);
	if (padlen < 1 + 8)
		padlen += 64;
	RMD160Update(ctx, PADDING, padlen - 8);		/* padlen - 8 <= 64 */
	RMD160Update(ctx, size, 8);

	if (digest != NULL)
		for (i = 0; i < 5; i++)
			PUT_32BIT_LE(digest + i*4, ctx->state[i]);

	memset(ctx, 0, sizeof (*ctx));
}