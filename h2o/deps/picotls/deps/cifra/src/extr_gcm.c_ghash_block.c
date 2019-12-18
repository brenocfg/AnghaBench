#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  Y; int /*<<< orphan*/  H; } ;
typedef  TYPE_1__ ghash_ctx ;
typedef  int /*<<< orphan*/  cf_gf128 ;

/* Variables and functions */
 int /*<<< orphan*/  cf_gf128_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_gf128_frombytes_be (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_gf128_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ghash_block(void *vctx, const uint8_t *data)
{
  ghash_ctx *ctx = vctx;
  cf_gf128 gfdata;
  cf_gf128_frombytes_be(data, gfdata);
  cf_gf128_add(gfdata, ctx->Y, ctx->Y);
  cf_gf128_mul(ctx->Y, ctx->H, ctx->Y);
}