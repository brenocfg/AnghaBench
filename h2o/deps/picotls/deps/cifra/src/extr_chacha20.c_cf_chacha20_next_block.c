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
struct TYPE_2__ {int /*<<< orphan*/  ncounter; int /*<<< orphan*/  nonce; int /*<<< orphan*/  constant; int /*<<< orphan*/  key1; int /*<<< orphan*/  key0; } ;
typedef  TYPE_1__ cf_chacha20_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  cf_chacha20_core (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  incr_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cf_chacha20_next_block(void *vctx, uint8_t *out)
{
  cf_chacha20_ctx *ctx = vctx;
  cf_chacha20_core(ctx->key0,
                   ctx->key1,
                   ctx->nonce,
                   ctx->constant,
                   out);
  incr_le(ctx->nonce, ctx->ncounter);
}