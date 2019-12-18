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
struct TYPE_5__ {int /*<<< orphan*/  class2_intr_base; int /*<<< orphan*/  slb_flt_base; } ;
struct spu_context {int flags; int /*<<< orphan*/  state; int /*<<< orphan*/  csa; int /*<<< orphan*/ * ops; struct spu* spu; int /*<<< orphan*/  owner; TYPE_1__ stats; } ;
struct TYPE_6__ {int /*<<< orphan*/  class2_intr; int /*<<< orphan*/  slb_flt; } ;
struct spu {size_t node; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  register_lock; int /*<<< orphan*/  mfc_callback; int /*<<< orphan*/  stop_callback; int /*<<< orphan*/  wbox_callback; int /*<<< orphan*/  ibox_callback; int /*<<< orphan*/  tgid; int /*<<< orphan*/  pid; scalar_t__ flags; struct spu_context* ctx; TYPE_2__ stats; } ;
struct TYPE_8__ {int /*<<< orphan*/  reserved_spus; } ;
struct TYPE_7__ {int /*<<< orphan*/  tgid; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int SPU_CREATE_NOSCHED ; 
 int /*<<< orphan*/  SPU_STATE_RUNNABLE ; 
 int /*<<< orphan*/  SPU_UTIL_SYSTEM ; 
 int /*<<< orphan*/  SPU_UTIL_USER ; 
 int /*<<< orphan*/  SWITCH_LOG_START ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_4__* cbe_spu_info ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_associate_mm (struct spu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu_bind_context__enter ; 
 int /*<<< orphan*/  spu_context_trace (int /*<<< orphan*/ ,struct spu_context*,struct spu*) ; 
 int /*<<< orphan*/  spu_hw_ops ; 
 int /*<<< orphan*/  spu_restore (int /*<<< orphan*/ *,struct spu*) ; 
 int /*<<< orphan*/  spu_switch_log_notify (struct spu*,struct spu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu_switch_notify (struct spu*,struct spu_context*) ; 
 int /*<<< orphan*/  spu_unmap_mappings (struct spu_context*) ; 
 int /*<<< orphan*/  spuctx_switch_state (struct spu_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spufs_ibox_callback ; 
 int /*<<< orphan*/  spufs_mfc_callback ; 
 int /*<<< orphan*/  spufs_stop_callback ; 
 int /*<<< orphan*/  spufs_wbox_callback ; 

__attribute__((used)) static void spu_bind_context(struct spu *spu, struct spu_context *ctx)
{
	spu_context_trace(spu_bind_context__enter, ctx, spu);

	spuctx_switch_state(ctx, SPU_UTIL_SYSTEM);

	if (ctx->flags & SPU_CREATE_NOSCHED)
		atomic_inc(&cbe_spu_info[spu->node].reserved_spus);

	ctx->stats.slb_flt_base = spu->stats.slb_flt;
	ctx->stats.class2_intr_base = spu->stats.class2_intr;

	spu_associate_mm(spu, ctx->owner);

	spin_lock_irq(&spu->register_lock);
	spu->ctx = ctx;
	spu->flags = 0;
	ctx->spu = spu;
	ctx->ops = &spu_hw_ops;
	spu->pid = current->pid;
	spu->tgid = current->tgid;
	spu->ibox_callback = spufs_ibox_callback;
	spu->wbox_callback = spufs_wbox_callback;
	spu->stop_callback = spufs_stop_callback;
	spu->mfc_callback = spufs_mfc_callback;
	spin_unlock_irq(&spu->register_lock);

	spu_unmap_mappings(ctx);

	spu_switch_log_notify(spu, ctx, SWITCH_LOG_START, 0);
	spu_restore(&ctx->csa, spu);
	spu->timestamp = jiffies;
	spu_switch_notify(spu, ctx);
	ctx->state = SPU_STATE_RUNNABLE;

	spuctx_switch_state(ctx, SPU_UTIL_USER);
}