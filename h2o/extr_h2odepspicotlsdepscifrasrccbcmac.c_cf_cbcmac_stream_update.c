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
struct TYPE_6__ {TYPE_1__* prp; int /*<<< orphan*/  used; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_2__ cf_cbcmac_stream ;
struct TYPE_5__ {int /*<<< orphan*/  blocksz; } ;

/* Variables and functions */
 int /*<<< orphan*/  cbcmac_process ; 
 int /*<<< orphan*/  cf_blockwise_accumulate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,TYPE_2__*) ; 

void cf_cbcmac_stream_update(cf_cbcmac_stream *ctx, const uint8_t *data, size_t len)
{
  cf_blockwise_accumulate(ctx->buffer, &ctx->used, ctx->prp->blocksz,
                          data, len,
                          cbcmac_process,
                          ctx);
}