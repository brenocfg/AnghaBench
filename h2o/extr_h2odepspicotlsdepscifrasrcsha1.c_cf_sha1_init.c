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
typedef  TYPE_1__ cf_sha1_context ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void cf_sha1_init(cf_sha1_context *ctx)
{
  memset(ctx, 0, sizeof *ctx);
  ctx->H[0] = 0x67452301;
  ctx->H[1] = 0xefcdab89;
  ctx->H[2] = 0x98badcfe;
  ctx->H[3] = 0x10325476;
  ctx->H[4] = 0xc3d2e1f0;
}