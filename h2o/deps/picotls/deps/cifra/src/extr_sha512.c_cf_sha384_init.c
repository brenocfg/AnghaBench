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
struct TYPE_4__ {void** H; } ;
typedef  TYPE_1__ cf_sha512_context ;

/* Variables and functions */
 void* UINT64_C (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void cf_sha384_init(cf_sha512_context *ctx)
{
  memset(ctx, 0, sizeof *ctx);
  ctx->H[0] = UINT64_C(0xcbbb9d5dc1059ed8);
  ctx->H[1] = UINT64_C(0x629a292a367cd507);
  ctx->H[2] = UINT64_C(0x9159015a3070dd17);
  ctx->H[3] = UINT64_C(0x152fecd8f70e5939);
  ctx->H[4] = UINT64_C(0x67332667ffc00b31);
  ctx->H[5] = UINT64_C(0x8eb44a8768581511);
  ctx->H[6] = UINT64_C(0xdb0c2e0d64f98fa7);
  ctx->H[7] = UINT64_C(0x47b5481dbefa4fa4);
}