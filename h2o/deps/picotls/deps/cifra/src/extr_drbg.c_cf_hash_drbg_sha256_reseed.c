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
typedef  int uint8_t ;
struct TYPE_3__ {int reseed_counter; int /*<<< orphan*/  C; int /*<<< orphan*/  V; } ;
typedef  TYPE_1__ cf_hash_drbg_sha256 ;

/* Variables and functions */
 int /*<<< orphan*/  cf_sha256 ; 
 int /*<<< orphan*/  hash_df (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int,void const*,size_t,void const*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void cf_hash_drbg_sha256_reseed(cf_hash_drbg_sha256 *ctx,
                                const void *entropy, size_t nentropy,
                                const void *addnl, size_t naddnl)
{
  /* 1. seed_material = 0x01 || V || entropy_input || additional_input
   * 2. seed = Hash_df(seed_material, seedlen)
   * 3. V = seed */
  uint8_t one = 1;
  /* stash V in C, because it cannot alias output */
  memcpy(ctx->C, ctx->V, sizeof ctx->C);
  hash_df(&cf_sha256,
          &one, sizeof one,
          ctx->C, sizeof ctx->C,
          entropy, nentropy,
          addnl, naddnl,
          ctx->V, sizeof ctx->V);

  /* 4. C = Hash_df(0x00 || V, seedlen) */
  uint8_t zero = 0;
  hash_df(&cf_sha256,
          &zero, sizeof zero,
          ctx->V, sizeof ctx->V,
          NULL, 0,
          NULL, 0,
          ctx->C, sizeof ctx->C);

  /* 5. reseed_counter = 1 */
  ctx->reseed_counter = 1;
}