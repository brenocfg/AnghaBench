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
struct TYPE_6__ {scalar_t__ used; scalar_t__ buffer; TYPE_1__* prp; } ;
typedef  TYPE_2__ cf_cbcmac_stream ;
struct TYPE_5__ {scalar_t__ blocksz; } ;

/* Variables and functions */
 int /*<<< orphan*/  cbcmac_process (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

void cf_cbcmac_stream_finish_block_zero(cf_cbcmac_stream *ctx)
{
  if (ctx->used == 0)
    return;

  memset(ctx->buffer + ctx->used, 0, ctx->prp->blocksz - ctx->used);
  cbcmac_process(ctx, ctx->buffer);
  ctx->used = 0;
}