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
struct TYPE_4__ {scalar_t__ b64; } ;
struct TYPE_5__ {int* v; int rounds_compr; int rounds_final; int initialized; scalar_t__ buflen; scalar_t__ bytes; TYPE_1__ buf; } ;
typedef  TYPE_2__ SIPHASH_CTX ;

/* Variables and functions */

void
SipHash_InitX(SIPHASH_CTX *ctx, int rc, int rf)
{

	ctx->v[0] = 0x736f6d6570736575ull;
	ctx->v[1] = 0x646f72616e646f6dull;
	ctx->v[2] = 0x6c7967656e657261ull;
	ctx->v[3] = 0x7465646279746573ull;
	ctx->buf.b64 = 0;
	ctx->bytes = 0;
	ctx->buflen = 0;
	ctx->rounds_compr = rc;
	ctx->rounds_final = rf;
	ctx->initialized = 1;
}