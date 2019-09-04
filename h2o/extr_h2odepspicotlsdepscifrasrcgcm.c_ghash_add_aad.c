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
struct TYPE_4__ {scalar_t__ state; size_t len_aad; } ;
typedef  TYPE_1__ ghash_ctx ;

/* Variables and functions */
 scalar_t__ STATE_AAD ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ghash_add (TYPE_1__*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void ghash_add_aad(ghash_ctx *ctx, const uint8_t *buf, size_t n)
{
  assert(ctx->state == STATE_AAD);
  ctx->len_aad += n;
  ghash_add(ctx, buf, n);
}