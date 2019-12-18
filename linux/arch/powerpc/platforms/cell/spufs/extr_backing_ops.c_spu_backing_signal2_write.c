#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int spu_cfg_RW; } ;
struct TYPE_4__ {int* spu_chnlcnt_RW; int /*<<< orphan*/  register_lock; int /*<<< orphan*/ * spu_chnldata_RW; TYPE_1__ priv2; } ;
struct spu_context {TYPE_2__ csa; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFC_SIGNAL_2_EVENT ; 
 int /*<<< orphan*/  gen_spu_event (struct spu_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spu_backing_signal2_write(struct spu_context *ctx, u32 data)
{
	spin_lock(&ctx->csa.register_lock);
	if (ctx->csa.priv2.spu_cfg_RW & 0x2)
		ctx->csa.spu_chnldata_RW[4] |= data;
	else
		ctx->csa.spu_chnldata_RW[4] = data;
	ctx->csa.spu_chnlcnt_RW[4] = 1;
	gen_spu_event(ctx, MFC_SIGNAL_2_EVENT);
	spin_unlock(&ctx->csa.register_lock);
}