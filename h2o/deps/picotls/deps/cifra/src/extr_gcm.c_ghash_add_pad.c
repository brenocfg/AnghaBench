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
struct TYPE_4__ {scalar_t__ buffer_used; scalar_t__ buffer; } ;
typedef  TYPE_1__ ghash_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  ghash_block (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ghash_add_pad(ghash_ctx *ctx)
{
  if (ctx->buffer_used == 0)
    return;

  memset(ctx->buffer + ctx->buffer_used, 0, sizeof(ctx->buffer) - ctx->buffer_used);
  ghash_block(ctx, ctx->buffer);
  ctx->buffer_used = 0;
}