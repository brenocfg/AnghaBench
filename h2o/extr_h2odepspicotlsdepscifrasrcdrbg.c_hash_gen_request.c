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
struct TYPE_4__ {int /*<<< orphan*/  reseed_counter; int /*<<< orphan*/  C; int /*<<< orphan*/  V; } ;
typedef  TYPE_1__ cf_hash_drbg_sha256 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cf_hash_drbg_sha256_needs_reseed (TYPE_1__*) ; 
 int /*<<< orphan*/  cf_sha256 ; 
 int /*<<< orphan*/  hash_generate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,void*,size_t) ; 
 int /*<<< orphan*/  hash_process_addnl (int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hash_step (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hash_gen_request(cf_hash_drbg_sha256 *ctx,
                             const void *addnl, size_t naddnl,
                             void *out, size_t nout)
{
  uint8_t data[440/8]; /* a temporary copy of V, which gets incremented by generate */

  assert(!cf_hash_drbg_sha256_needs_reseed(ctx));

  hash_process_addnl(&cf_sha256, addnl, naddnl, ctx->V, sizeof ctx->V);
  assert(sizeof data == sizeof ctx->V);
  memcpy(data, ctx->V, sizeof ctx->V);
  hash_generate(&cf_sha256, data, sizeof data, out, nout);
  hash_step(&cf_sha256, ctx->V, sizeof ctx->V, ctx->C, sizeof ctx->C, &ctx->reseed_counter);
}