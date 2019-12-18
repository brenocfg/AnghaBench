#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  inner; TYPE_1__* hash; } ;
typedef  TYPE_2__ cf_hmac_ctx ;
struct TYPE_4__ {int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,void const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,void const*,size_t) ; 

void cf_hmac_update(cf_hmac_ctx *ctx, const void *data, size_t ndata)
{
  assert(ctx && ctx->hash);

  ctx->hash->update(&ctx->inner, data, ndata);
}