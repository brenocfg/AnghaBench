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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int ncounter; scalar_t__ nblock; scalar_t__ nonce; int /*<<< orphan*/  constant; scalar_t__ key1; scalar_t__ key0; } ;
typedef  TYPE_1__ cf_salsa20_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  salsa20_sigma ; 
 int /*<<< orphan*/  salsa20_tau ; 

void cf_salsa20_init(cf_salsa20_ctx *ctx, const uint8_t *key, size_t nkey, const uint8_t nonce[8])
{
  switch (nkey)
  {
    case 16:
      memcpy(ctx->key0, key, 16);
      memcpy(ctx->key1, key, 16);
      ctx->constant = salsa20_tau;
      break;
    case 32:
      memcpy(ctx->key0, key, 16);
      memcpy(ctx->key1, key + 16, 16);
      ctx->constant = salsa20_sigma;
      break;
    default:
      abort();
  }

  memset(ctx->nonce, 0, sizeof ctx->nonce);
  memcpy(ctx->nonce + 8, nonce, 8);
  ctx->nblock = 0;
  ctx->ncounter = 8;
}