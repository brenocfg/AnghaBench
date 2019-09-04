#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {TYPE_1__* prp; } ;
struct TYPE_6__ {TYPE_2__ cmac; int /*<<< orphan*/  processed; int /*<<< orphan*/  cbc; } ;
typedef  TYPE_3__ cf_cmac_stream ;
struct TYPE_4__ {scalar_t__ blocksz; } ;

/* Variables and functions */
 int CF_MAXBLOCK ; 
 int /*<<< orphan*/  cf_cbc_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void cmac_process(void *vctx, const uint8_t *block)
{
  cf_cmac_stream *ctx = vctx;
  uint8_t output[CF_MAXBLOCK];
  cf_cbc_encrypt(&ctx->cbc, block, output, 1);
  ctx->processed += ctx->cmac.prp->blocksz;
}