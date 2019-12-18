#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct streebog_state {int fillsize; int* buffer; } ;

/* Variables and functions */
 int STREEBOG_BLOCK_SIZE ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void streebog_pad(struct streebog_state *ctx)
{
	if (ctx->fillsize >= STREEBOG_BLOCK_SIZE)
		return;

	memset(ctx->buffer + ctx->fillsize, 0,
	       sizeof(ctx->buffer) - ctx->fillsize);

	ctx->buffer[ctx->fillsize] = 1;
}