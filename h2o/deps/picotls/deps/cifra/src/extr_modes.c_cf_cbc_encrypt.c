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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  block; int /*<<< orphan*/  prpctx; TYPE_1__* prp; } ;
typedef  TYPE_2__ cf_cbc ;
struct TYPE_4__ {size_t blocksz; int /*<<< orphan*/  (* encrypt ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int CF_MAXBLOCK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xor_bb (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t) ; 

void cf_cbc_encrypt(cf_cbc *ctx, const uint8_t *input, uint8_t *output, size_t blocks)
{
  uint8_t buf[CF_MAXBLOCK];
  size_t nblk = ctx->prp->blocksz;

  while (blocks--)
  {
    xor_bb(buf, input, ctx->block, nblk);
    ctx->prp->encrypt(ctx->prpctx, buf, ctx->block);
    memcpy(output, ctx->block, nblk);
    input += nblk;
    output += nblk;
  }
}