#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {TYPE_1__* prp; } ;
struct TYPE_9__ {int used; scalar_t__ processed; int /*<<< orphan*/  buffer; int /*<<< orphan*/  finalised; TYPE_2__ cmac; } ;
typedef  TYPE_3__ cf_cmac_stream ;
typedef  int /*<<< orphan*/  cf_blockwise_in_fn ;
struct TYPE_7__ {size_t blocksz; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cf_blockwise_acc_pad (int /*<<< orphan*/ ,scalar_t__*,size_t,int,int,int,scalar_t__,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  cf_blockwise_accumulate_final (int /*<<< orphan*/ ,scalar_t__*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  cmac_process ; 
 int /*<<< orphan*/  cmac_process_final_nopad ; 
 int /*<<< orphan*/  cmac_process_final_pad ; 

void cf_cmac_stream_update(cf_cmac_stream *ctx, const uint8_t *data, size_t len, int isfinal)
{
  size_t blocksz = ctx->cmac.prp->blocksz;
  cf_blockwise_in_fn final_fn = cmac_process;
  int needpad = 0;

  if (isfinal)
  {
    int whole_number_of_blocks = ((len + ctx->used) & 0xf) == 0;
    int empty_message = len == 0 && ctx->used == 0 && ctx->processed == 0;

    assert(!ctx->finalised);  /* finalised before? */
    assert(len != 0 || empty_message); /* we can't be told we're done after the fact. */

    /* If we have a whole number of blocks, and at least 1 block, we XOR in B.
     * Otherwise, we need to pad and XOR in P. */
    if (whole_number_of_blocks && !empty_message)
      final_fn = cmac_process_final_nopad;
    else
      needpad = 1;
  }

  /* Input data */
  cf_blockwise_accumulate_final(ctx->buffer, &ctx->used, blocksz,
                                data, len,
                                cmac_process,
                                final_fn, ctx);

  /* Input padding */
  if (needpad)
  {
    cf_blockwise_acc_pad(ctx->buffer, &ctx->used, blocksz,
                         0x80, 0x00, 0x00, blocksz - ctx->used,
                         cmac_process_final_pad, ctx);
  }
}