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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  state; int /*<<< orphan*/  H; } ;
typedef  TYPE_1__ ghash_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_AAD ; 
 int /*<<< orphan*/  cf_gf128_frombytes_be (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ghash_init(ghash_ctx *ctx, uint8_t H[16])
{
  memset(ctx, 0, sizeof *ctx);
  cf_gf128_frombytes_be(H, ctx->H);
  ctx->state = STATE_AAD;
}