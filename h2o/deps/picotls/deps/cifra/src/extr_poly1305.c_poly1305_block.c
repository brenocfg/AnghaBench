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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  r; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ cf_poly1305 ;

/* Variables and functions */
 int /*<<< orphan*/  poly1305_add (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  poly1305_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void poly1305_block(cf_poly1305 *ctx,
                           const uint32_t c[17])
{
  poly1305_add(ctx->h, c);
  poly1305_mul(ctx->h, ctx->r);
}