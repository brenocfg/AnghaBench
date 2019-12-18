#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  int_mask_class2_RW; } ;
struct TYPE_6__ {int mb_stat_R; } ;
struct TYPE_5__ {int /*<<< orphan*/  puint_mb_R; } ;
struct TYPE_8__ {int* spu_chnlcnt_RW; int /*<<< orphan*/  register_lock; TYPE_3__ priv1; TYPE_2__ prob; TYPE_1__ priv2; } ;
struct spu_context {TYPE_4__ csa; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS2_ENABLE_MAILBOX_INTR ; 
 int /*<<< orphan*/  MFC_PU_INT_MAILBOX_AVAILABLE_EVENT ; 
 int /*<<< orphan*/  gen_spu_event (struct spu_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spu_backing_ibox_read(struct spu_context *ctx, u32 * data)
{
	int ret;

	spin_lock(&ctx->csa.register_lock);
	if (ctx->csa.prob.mb_stat_R & 0xff0000) {
		/* Read the first available word.
		 * Implementation note: the depth
		 * of puint_mb_R is currently 1.
		 */
		*data = ctx->csa.priv2.puint_mb_R;
		ctx->csa.prob.mb_stat_R &= ~(0xff0000);
		ctx->csa.spu_chnlcnt_RW[30] = 1;
		gen_spu_event(ctx, MFC_PU_INT_MAILBOX_AVAILABLE_EVENT);
		ret = 4;
	} else {
		/* make sure we get woken up by the interrupt */
		ctx->csa.priv1.int_mask_class2_RW |= CLASS2_ENABLE_MAILBOX_INTR;
		ret = 0;
	}
	spin_unlock(&ctx->csa.register_lock);
	return ret;
}