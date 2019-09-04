#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  cf_hmac_drbg ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_DRBG_GENERATE ; 
 size_t MIN (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  hmac_drbg_generate (int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ *,size_t) ; 

void cf_hmac_drbg_gen_additional(cf_hmac_drbg *ctx,
                                 const void *addnl, size_t naddnl,
                                 void *out, size_t nout)
{
  uint8_t *bout = out;

  while (nout != 0)
  {
    size_t take = MIN(MAX_DRBG_GENERATE, nout);
    hmac_drbg_generate(ctx, addnl, naddnl, bout, take);
    bout += take;
    nout -= take;

    /* Add additional data only once. */
    addnl = NULL;
    naddnl = 0;
  }
}