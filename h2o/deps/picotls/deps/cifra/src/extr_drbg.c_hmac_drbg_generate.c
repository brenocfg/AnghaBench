#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {TYPE_1__* hash; } ;
struct TYPE_10__ {int /*<<< orphan*/  reseed_counter; int /*<<< orphan*/  V; TYPE_3__ hmac; } ;
typedef  TYPE_2__ cf_hmac_drbg ;
typedef  TYPE_3__ cf_hmac_ctx ;
struct TYPE_9__ {int /*<<< orphan*/  hashsz; } ;

/* Variables and functions */
 size_t MIN (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cf_hmac_drbg_needs_reseed (TYPE_2__*) ; 
 int /*<<< orphan*/  cf_hmac_finish (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_hmac_update (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hmac_drbg_update (TYPE_2__*,void const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void hmac_drbg_generate(cf_hmac_drbg *ctx,
                               const void *addnl, size_t naddnl,
                               void *out, size_t nout)
{
  /* 1. If reseed_counter > reseed_interval, then return an indication
   * that a reseed is required */
  assert(!cf_hmac_drbg_needs_reseed(ctx));

  /* 2. If additional_input != null, then
   *    (Key, V) = HMAC_DRBG_Update(additional_input, Key, V)
   */
  if (naddnl)
    hmac_drbg_update(ctx, addnl, naddnl, NULL, 0, NULL, 0);

  /* 3. temp = Null
   * 4. While (len(temp) < requested_number_of_bits) do:
   *   4.1. V = HMAC(Key, V)
   *   4.2. temp = temp || V
   * 5. returned_bits = leftmost(temp, requested_number_of_bits)
   *
   * We write the contents of temp directly into the caller's
   * out buffer.
   */
  uint8_t *bout = out;
  cf_hmac_ctx local;

  while (nout)
  {
    local = ctx->hmac;
    cf_hmac_update(&local, ctx->V, ctx->hmac.hash->hashsz);
    cf_hmac_finish(&local, ctx->V);

    size_t take = MIN(ctx->hmac.hash->hashsz, nout);
    memcpy(bout, ctx->V, take);
    bout += take;
    nout -= take;
  }

  /* 6. (Key, V) = HMAC_DRBG_Update(additional_input, Key, V) */
  hmac_drbg_update(ctx, addnl, naddnl, NULL, 0, NULL, 0);

  /* 7. reseed_counter = reseed_counter + 1 */
  ctx->reseed_counter++;
}