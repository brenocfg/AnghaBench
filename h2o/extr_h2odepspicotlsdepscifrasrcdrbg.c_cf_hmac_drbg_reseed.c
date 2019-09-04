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
struct TYPE_4__ {int reseed_counter; } ;
typedef  TYPE_1__ cf_hmac_drbg ;

/* Variables and functions */
 int /*<<< orphan*/  hmac_drbg_update (TYPE_1__*,void const*,size_t,void const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void cf_hmac_drbg_reseed(cf_hmac_drbg *ctx,
                         const void *entropy, size_t nentropy,
                         const void *addnl, size_t naddnl)
{
  /* 1. seed_material = entropy_input || additional_input
   * 2. (Key, V) = HMAC_DRBG_Update(seed_material, Key, V) */
  hmac_drbg_update(ctx, entropy, nentropy, addnl, naddnl, NULL, 0);
  
  /* 3. reseed_counter = 1 */
  ctx->reseed_counter = 1;
}