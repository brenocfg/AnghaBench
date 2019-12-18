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
struct TYPE_3__ {int /*<<< orphan*/  constant; int /*<<< orphan*/  key1; int /*<<< orphan*/  key0; } ;
typedef  TYPE_1__ cf_chacha20_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  chacha20_sigma ; 
 int /*<<< orphan*/  chacha20_tau ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void set_key(cf_chacha20_ctx *ctx, const uint8_t *key, size_t nkey)
{
  switch (nkey)
  {
    case 16:
      memcpy(ctx->key0, key, 16);
      memcpy(ctx->key1, key, 16);
      ctx->constant = chacha20_tau;
      break;
    case 32:
      memcpy(ctx->key0, key, 16);
      memcpy(ctx->key1, key + 16, 16);
      ctx->constant = chacha20_sigma;
      break;
    default:
      abort();
  }
}