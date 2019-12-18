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
struct TYPE_4__ {int* H; } ;
typedef  TYPE_1__ cf_sha256_context ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void cf_sha224_init(cf_sha256_context *ctx)
{
  memset(ctx, 0, sizeof *ctx);
  ctx->H[0] = 0xc1059ed8;
  ctx->H[1] = 0x367cd507;
  ctx->H[2] = 0x3070dd17;
  ctx->H[3] = 0xf70e5939;
  ctx->H[4] = 0xffc00b31;
  ctx->H[5] = 0x68581511;
  ctx->H[6] = 0x64f98fa7;
  ctx->H[7] = 0xbefa4fa4;
}