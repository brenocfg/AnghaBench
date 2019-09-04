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
typedef  int uint8_t ;
struct TYPE_4__ {int* r; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ cf_poly1305 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void cf_poly1305_init(cf_poly1305 *ctx,
                      const uint8_t r[16],
                      const uint8_t s[16])
{
  memset(ctx, 0, sizeof *ctx);

  ctx->r[0]  = r[0];
  ctx->r[1]  = r[1];
  ctx->r[2]  = r[2];
  ctx->r[3]  = r[3] & 0x0f;
  ctx->r[4]  = r[4] & 0xfc;
  ctx->r[5]  = r[5];
  ctx->r[6]  = r[6];
  ctx->r[7]  = r[7] & 0x0f;
  ctx->r[8]  = r[8] & 0xfc;
  ctx->r[9]  = r[9];
  ctx->r[10] = r[10];
  ctx->r[11] = r[11] & 0x0f;
  ctx->r[12] = r[12] & 0xfc;
  ctx->r[13] = r[13];
  ctx->r[14] = r[14];
  ctx->r[15] = r[15] & 0x0f;
  ctx->r[16] = 0;

  memcpy(ctx->s, s, 16);
}