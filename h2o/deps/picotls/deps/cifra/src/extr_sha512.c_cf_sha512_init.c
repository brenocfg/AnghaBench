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

void cf_sha512_init(cf_sha512_context *ctx)
{
  memset(ctx, 0, sizeof *ctx);
  ctx->H[0] = UINT64_C(0x6a09e667f3bcc908);
  ctx->H[1] = UINT64_C(0xbb67ae8584caa73b);
  ctx->H[2] = UINT64_C(0x3c6ef372fe94f82b);
  ctx->H[3] = UINT64_C(0xa54ff53a5f1d36f1);
  ctx->H[4] = UINT64_C(0x510e527fade682d1);
  ctx->H[5] = UINT64_C(0x9b05688c2b3e6c1f);
  ctx->H[6] = UINT64_C(0x1f83d9abfb41bd6b);
  ctx->H[7] = UINT64_C(0x5be0cd19137e2179);
}