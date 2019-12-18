#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spu_gang {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tstamp; int /*<<< orphan*/  util_state; } ;
struct spu_context {TYPE_1__ stats; int /*<<< orphan*/  aff_list; int /*<<< orphan*/  rq; int /*<<< orphan*/  owner; int /*<<< orphan*/ * ops; int /*<<< orphan*/  state; int /*<<< orphan*/  run_wq; int /*<<< orphan*/  mfc_wq; int /*<<< orphan*/  stop_wq; int /*<<< orphan*/  wbox_wq; int /*<<< orphan*/  ibox_wq; int /*<<< orphan*/  run_mutex; int /*<<< orphan*/  state_mutex; int /*<<< orphan*/  kref; int /*<<< orphan*/  mapping_lock; int /*<<< orphan*/  mmio_lock; int /*<<< orphan*/  csa; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPU_STATE_SAVED ; 
 int /*<<< orphan*/  SPU_UTIL_IDLE_LOADED ; 
 int /*<<< orphan*/  __spu_update_sched_info (struct spu_context*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  get_task_mm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct spu_context*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 struct spu_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_spu_contexts ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_backing_ops ; 
 int /*<<< orphan*/  spu_gang_add_ctx (struct spu_gang*,struct spu_context*) ; 
 scalar_t__ spu_init_csa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_set_timeslice (struct spu_context*) ; 

struct spu_context *alloc_spu_context(struct spu_gang *gang)
{
	struct spu_context *ctx;

	ctx = kzalloc(sizeof *ctx, GFP_KERNEL);
	if (!ctx)
		goto out;
	/* Binding to physical processor deferred
	 * until spu_activate().
	 */
	if (spu_init_csa(&ctx->csa))
		goto out_free;
	spin_lock_init(&ctx->mmio_lock);
	mutex_init(&ctx->mapping_lock);
	kref_init(&ctx->kref);
	mutex_init(&ctx->state_mutex);
	mutex_init(&ctx->run_mutex);
	init_waitqueue_head(&ctx->ibox_wq);
	init_waitqueue_head(&ctx->wbox_wq);
	init_waitqueue_head(&ctx->stop_wq);
	init_waitqueue_head(&ctx->mfc_wq);
	init_waitqueue_head(&ctx->run_wq);
	ctx->state = SPU_STATE_SAVED;
	ctx->ops = &spu_backing_ops;
	ctx->owner = get_task_mm(current);
	INIT_LIST_HEAD(&ctx->rq);
	INIT_LIST_HEAD(&ctx->aff_list);
	if (gang)
		spu_gang_add_ctx(gang, ctx);

	__spu_update_sched_info(ctx);
	spu_set_timeslice(ctx);
	ctx->stats.util_state = SPU_UTIL_IDLE_LOADED;
	ctx->stats.tstamp = ktime_get_ns();

	atomic_inc(&nr_spu_contexts);
	goto out;
out_free:
	kfree(ctx);
	ctx = NULL;
out:
	return ctx;
}