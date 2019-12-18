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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/ * s; } ;
typedef  TYPE_1__ norx32_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  permute (TYPE_1__*) ; 

__attribute__((used)) static void switch_domain(norx32_ctx *ctx, uint32_t constant)
{
  ctx->s[15] ^= constant;
  permute(ctx);
}