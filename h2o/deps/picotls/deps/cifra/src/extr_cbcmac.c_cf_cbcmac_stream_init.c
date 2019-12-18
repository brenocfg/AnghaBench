#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cf_prp ;
struct TYPE_5__ {void* prpctx; int /*<<< orphan*/  const* prp; } ;
typedef  TYPE_1__ cf_cbcmac_stream ;

/* Variables and functions */
 int /*<<< orphan*/  cf_cbcmac_stream_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void cf_cbcmac_stream_init(cf_cbcmac_stream *ctx, const cf_prp *prp, void *prpctx)
{
  memset(ctx, 0, sizeof *ctx);
  ctx->prp = prp;
  ctx->prpctx = prpctx;
  cf_cbcmac_stream_reset(ctx);
}