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
struct TYPE_4__ {int ncounter; scalar_t__ nblock; scalar_t__ nonce; } ;
typedef  TYPE_1__ cf_chacha20_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_key (TYPE_1__*,int /*<<< orphan*/  const*,size_t) ; 

void cf_chacha20_init(cf_chacha20_ctx *ctx, const uint8_t *key, size_t nkey, const uint8_t nonce[8])
{
  set_key(ctx, key, nkey);
  memset(ctx->nonce, 0, sizeof ctx->nonce);
  memcpy(ctx->nonce + 8, nonce, 8);
  ctx->nblock = 0;
  ctx->ncounter = 8;
}