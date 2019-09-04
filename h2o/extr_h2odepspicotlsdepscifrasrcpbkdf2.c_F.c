#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {TYPE_1__* hash; } ;
typedef  TYPE_2__ cf_hmac_ctx ;
struct TYPE_6__ {size_t hashsz; } ;

/* Variables and functions */
 int CF_MAXHASH ; 
 int /*<<< orphan*/  cf_hmac_finish (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cf_hmac_update (TYPE_2__*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  write32_be (scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xor_bb (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void F(const cf_hmac_ctx *startctx,
              uint32_t counter,
              const uint8_t *salt, size_t nsalt,
              uint32_t iterations,
              uint8_t *out)
{
  uint8_t U[CF_MAXHASH];
  size_t hashsz = startctx->hash->hashsz;
  
  uint8_t countbuf[4];
  write32_be(counter, countbuf);

  /* First iteration:
   *   U_1 = PRF(P, S || INT_32_BE(i))
   */
  cf_hmac_ctx ctx = *startctx;
  cf_hmac_update(&ctx, salt, nsalt);
  cf_hmac_update(&ctx, countbuf, sizeof countbuf);
  cf_hmac_finish(&ctx, U);
  memcpy(out, U, hashsz);

  /* Subsequent iterations:
   *   U_c = PRF(P, U_{c-1})
   */
  for (uint32_t i = 1; i < iterations; i++)
  {
    ctx = *startctx;
    cf_hmac_update(&ctx, U, hashsz);
    cf_hmac_finish(&ctx, U);
    xor_bb(out, out, U, hashsz);
  }
}