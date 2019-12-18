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
struct TYPE_3__ {int* state; scalar_t__* count; } ;
typedef  TYPE_1__ SHA384_CTX ;

/* Variables and functions */

void
SHA384_Init(SHA384_CTX * ctx)
{

	/* Zero bits processed so far */
	ctx->count[0] = ctx->count[1] = 0;

	/* Magic initialization constants */
	ctx->state[0] = 0xcbbb9d5dc1059ed8ULL;
	ctx->state[1] = 0x629a292a367cd507ULL;
	ctx->state[2] = 0x9159015a3070dd17ULL;
	ctx->state[3] = 0x152fecd8f70e5939ULL;
	ctx->state[4] = 0x67332667ffc00b31ULL;
	ctx->state[5] = 0x8eb44a8768581511ULL;
	ctx->state[6] = 0xdb0c2e0d64f98fa7ULL;
	ctx->state[7] = 0x47b5481dbefa4fa4ULL;
}