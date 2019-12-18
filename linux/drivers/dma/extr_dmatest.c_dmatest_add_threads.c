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
struct TYPE_2__ {int /*<<< orphan*/ * wait; } ;
struct dmatest_thread {int type; int pending; int /*<<< orphan*/  node; int /*<<< orphan*/  task; int /*<<< orphan*/  done_wait; TYPE_1__ test_done; struct dma_chan* chan; struct dmatest_info* info; } ;
struct dmatest_params {unsigned int threads_per_chan; } ;
struct dmatest_info {struct dmatest_params params; } ;
struct dmatest_chan {int /*<<< orphan*/  threads; struct dma_chan* chan; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_transaction_type { ____Placeholder_dma_transaction_type } dma_transaction_type ;

/* Variables and functions */
 int DMA_MEMCPY ; 
 int DMA_MEMSET ; 
 int DMA_PQ ; 
 int DMA_XOR ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_chan_name (struct dma_chan*) ; 
 int /*<<< orphan*/  dmatest_func ; 
 int /*<<< orphan*/  get_task_struct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dmatest_thread*) ; 
 int /*<<< orphan*/  kthread_create (int /*<<< orphan*/ ,struct dmatest_thread*,char*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct dmatest_thread* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static int dmatest_add_threads(struct dmatest_info *info,
		struct dmatest_chan *dtc, enum dma_transaction_type type)
{
	struct dmatest_params *params = &info->params;
	struct dmatest_thread *thread;
	struct dma_chan *chan = dtc->chan;
	char *op;
	unsigned int i;

	if (type == DMA_MEMCPY)
		op = "copy";
	else if (type == DMA_MEMSET)
		op = "set";
	else if (type == DMA_XOR)
		op = "xor";
	else if (type == DMA_PQ)
		op = "pq";
	else
		return -EINVAL;

	for (i = 0; i < params->threads_per_chan; i++) {
		thread = kzalloc(sizeof(struct dmatest_thread), GFP_KERNEL);
		if (!thread) {
			pr_warn("No memory for %s-%s%u\n",
				dma_chan_name(chan), op, i);
			break;
		}
		thread->info = info;
		thread->chan = dtc->chan;
		thread->type = type;
		thread->test_done.wait = &thread->done_wait;
		init_waitqueue_head(&thread->done_wait);
		smp_wmb();
		thread->task = kthread_create(dmatest_func, thread, "%s-%s%u",
				dma_chan_name(chan), op, i);
		if (IS_ERR(thread->task)) {
			pr_warn("Failed to create thread %s-%s%u\n",
				dma_chan_name(chan), op, i);
			kfree(thread);
			break;
		}

		/* srcbuf and dstbuf are allocated by the thread itself */
		get_task_struct(thread->task);
		list_add_tail(&thread->node, &dtc->threads);
		thread->pending = true;
	}

	return i;
}