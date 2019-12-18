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
typedef  int /*<<< orphan*/  u64 ;
struct dma_fence_array_cb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;
struct dma_fence_array {int num_fences; TYPE_1__ base; struct dma_fence** fences; int /*<<< orphan*/  num_pending; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PENDING_ERROR ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dma_fence_array_ops ; 
 int /*<<< orphan*/  dma_fence_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  init_irq_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dma_fence_array_work ; 
 struct dma_fence_array* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct dma_fence_array *dma_fence_array_create(int num_fences,
					       struct dma_fence **fences,
					       u64 context, unsigned seqno,
					       bool signal_on_any)
{
	struct dma_fence_array *array;
	size_t size = sizeof(*array);

	/* Allocate the callback structures behind the array. */
	size += num_fences * sizeof(struct dma_fence_array_cb);
	array = kzalloc(size, GFP_KERNEL);
	if (!array)
		return NULL;

	spin_lock_init(&array->lock);
	dma_fence_init(&array->base, &dma_fence_array_ops, &array->lock,
		       context, seqno);
	init_irq_work(&array->work, irq_dma_fence_array_work);

	array->num_fences = num_fences;
	atomic_set(&array->num_pending, signal_on_any ? 1 : num_fences);
	array->fences = fences;

	array->base.error = PENDING_ERROR;

	return array;
}