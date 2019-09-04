#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  outer; TYPE_1__* hash; int /*<<< orphan*/  inner; } ;
typedef  TYPE_2__ cf_hmac_ctx ;
struct TYPE_5__ {int /*<<< orphan*/  (* digest ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  hashsz; int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int CF_MAXHASH ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mem_clean (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void cf_hmac_finish(cf_hmac_ctx *ctx, uint8_t *out)
{
  assert(ctx && ctx->hash);
  assert(out);

  uint8_t innerh[CF_MAXHASH];
  ctx->hash->digest(&ctx->inner, innerh);

  ctx->hash->update(&ctx->outer, innerh, ctx->hash->hashsz);
  ctx->hash->digest(&ctx->outer, out);

  mem_clean(ctx, sizeof *ctx);
}