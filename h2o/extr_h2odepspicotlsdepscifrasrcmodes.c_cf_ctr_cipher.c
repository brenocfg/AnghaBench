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
struct TYPE_6__ {TYPE_1__* prp; int /*<<< orphan*/  nkeymat; int /*<<< orphan*/  keymat; } ;
typedef  TYPE_2__ cf_ctr ;
struct TYPE_5__ {int /*<<< orphan*/  blocksz; } ;

/* Variables and functions */
 int /*<<< orphan*/  cf_blockwise_xor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ctr_next_block ; 

void cf_ctr_cipher(cf_ctr *ctx, const uint8_t *input, uint8_t *output, size_t bytes)
{
  cf_blockwise_xor(ctx->keymat, &ctx->nkeymat,
                   ctx->prp->blocksz,
                   input, output, bytes,
                   ctr_next_block,
                   ctx);
}