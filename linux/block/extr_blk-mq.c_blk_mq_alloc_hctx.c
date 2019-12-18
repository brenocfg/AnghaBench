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
struct request_queue {int dummy; } ;
struct blk_mq_tag_set {int numa_node; int flags; int /*<<< orphan*/  cmd_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  entry; } ;
struct blk_mq_hw_ctx {int numa_node; int flags; int /*<<< orphan*/  cpumask; struct blk_mq_hw_ctx* ctxs; int /*<<< orphan*/  ctx_map; int /*<<< orphan*/  srcu; int /*<<< orphan*/  fq; TYPE_1__ dispatch_wait; int /*<<< orphan*/  dispatch_wait_lock; scalar_t__ nr_ctx; int /*<<< orphan*/  hctx_list; struct request_queue* queue; int /*<<< orphan*/  dispatch; int /*<<< orphan*/  lock; int /*<<< orphan*/  run_work; int /*<<< orphan*/  nr_active; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int BLK_MQ_F_BLOCKING ; 
 int BLK_MQ_F_TAG_SHARED ; 
 int GFP_NOIO ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NUMA_NO_NODE ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_alloc_flush_queue (struct request_queue*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blk_mq_dispatch_wake ; 
 int /*<<< orphan*/  blk_mq_hctx_kobj_init (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  blk_mq_hw_ctx_size (struct blk_mq_tag_set*) ; 
 int /*<<< orphan*/  blk_mq_run_work_fn ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int /*<<< orphan*/  init_srcu_struct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_func_entry (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct blk_mq_hw_ctx*) ; 
 struct blk_mq_hw_ctx* kmalloc_array_node (int /*<<< orphan*/ ,int,int,int) ; 
 struct blk_mq_hw_ctx* kzalloc_node (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nr_cpu_ids ; 
 int /*<<< orphan*/  sbitmap_free (int /*<<< orphan*/ *) ; 
 scalar_t__ sbitmap_init_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zalloc_cpumask_var_node (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static struct blk_mq_hw_ctx *
blk_mq_alloc_hctx(struct request_queue *q, struct blk_mq_tag_set *set,
		int node)
{
	struct blk_mq_hw_ctx *hctx;
	gfp_t gfp = GFP_NOIO | __GFP_NOWARN | __GFP_NORETRY;

	hctx = kzalloc_node(blk_mq_hw_ctx_size(set), gfp, node);
	if (!hctx)
		goto fail_alloc_hctx;

	if (!zalloc_cpumask_var_node(&hctx->cpumask, gfp, node))
		goto free_hctx;

	atomic_set(&hctx->nr_active, 0);
	if (node == NUMA_NO_NODE)
		node = set->numa_node;
	hctx->numa_node = node;

	INIT_DELAYED_WORK(&hctx->run_work, blk_mq_run_work_fn);
	spin_lock_init(&hctx->lock);
	INIT_LIST_HEAD(&hctx->dispatch);
	hctx->queue = q;
	hctx->flags = set->flags & ~BLK_MQ_F_TAG_SHARED;

	INIT_LIST_HEAD(&hctx->hctx_list);

	/*
	 * Allocate space for all possible cpus to avoid allocation at
	 * runtime
	 */
	hctx->ctxs = kmalloc_array_node(nr_cpu_ids, sizeof(void *),
			gfp, node);
	if (!hctx->ctxs)
		goto free_cpumask;

	if (sbitmap_init_node(&hctx->ctx_map, nr_cpu_ids, ilog2(8),
				gfp, node))
		goto free_ctxs;
	hctx->nr_ctx = 0;

	spin_lock_init(&hctx->dispatch_wait_lock);
	init_waitqueue_func_entry(&hctx->dispatch_wait, blk_mq_dispatch_wake);
	INIT_LIST_HEAD(&hctx->dispatch_wait.entry);

	hctx->fq = blk_alloc_flush_queue(q, hctx->numa_node, set->cmd_size,
			gfp);
	if (!hctx->fq)
		goto free_bitmap;

	if (hctx->flags & BLK_MQ_F_BLOCKING)
		init_srcu_struct(hctx->srcu);
	blk_mq_hctx_kobj_init(hctx);

	return hctx;

 free_bitmap:
	sbitmap_free(&hctx->ctx_map);
 free_ctxs:
	kfree(hctx->ctxs);
 free_cpumask:
	free_cpumask_var(hctx->cpumask);
 free_hctx:
	kfree(hctx);
 fail_alloc_hctx:
	return NULL;
}