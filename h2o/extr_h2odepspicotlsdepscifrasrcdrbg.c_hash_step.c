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
typedef  int const uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  cf_chash_ctx ;
struct TYPE_3__ {int hashsz; int /*<<< orphan*/  (* digest ) (int /*<<< orphan*/ *,int const*) ;int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,int const*,size_t) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ cf_chash ;

/* Variables and functions */
 int CF_MAXHASH ; 
 int /*<<< orphan*/  add (int const*,size_t,int const*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int const*,size_t) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int const*) ; 
 int /*<<< orphan*/  write32_be (scalar_t__,int const*) ; 

__attribute__((used)) static void hash_step(const cf_chash *H,
                      uint8_t *V, size_t nV,
                      const uint8_t *C, size_t nC,
                      uint32_t *reseed_counter)
{
  /* 4. h = Hash(0x03 || V) */
  uint8_t h[CF_MAXHASH];
  uint8_t three = 3;
  cf_chash_ctx ctx;

  H->init(&ctx);
  H->update(&ctx, &three, sizeof three);
  H->update(&ctx, V, nV);
  H->digest(&ctx, h);

  /* 5. V = (V + h + C + reseed_counter) mod 2 ^ seedlen */
  uint8_t reseed_counter_buf[4];
  write32_be(*reseed_counter, reseed_counter_buf);

  add(V, nV, h, H->hashsz);
  add(V, nV, C, nC);
  add(V, nV, reseed_counter_buf, sizeof reseed_counter_buf);

  /* 6. reseed_counter = reseed_counter + 1 */
  *reseed_counter = *reseed_counter + 1;
}