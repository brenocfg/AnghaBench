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
typedef  int /*<<< orphan*/  cf_hash_drbg_sha256 ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_DRBG_GENERATE ; 
 size_t MIN (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  hash_gen_request (int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ *,size_t) ; 

void cf_hash_drbg_sha256_gen_additional(cf_hash_drbg_sha256 *ctx,
                                        const void *addnl, size_t naddnl,
                                        void *out, size_t nout)
{
  uint8_t *bout = out;

  /* Generate output in requests of MAX_DRBG_GENERATE in size. */
  while (nout != 0)
  {
    size_t take = MIN(MAX_DRBG_GENERATE, nout);
    hash_gen_request(ctx, addnl, naddnl, bout, take);
    bout += take;
    nout -= take;

    /* Add additional data only once. */
    addnl = NULL;
    naddnl = 0;
  }
}