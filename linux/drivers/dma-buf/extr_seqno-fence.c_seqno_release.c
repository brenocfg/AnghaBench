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
struct seqno_fence {int /*<<< orphan*/  base; TYPE_1__* ops; int /*<<< orphan*/  sync_buf; } ;
struct dma_fence {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release ) (struct dma_fence*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dma_buf_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dma_fence*) ; 
 struct seqno_fence* to_seqno_fence (struct dma_fence*) ; 

__attribute__((used)) static void seqno_release(struct dma_fence *fence)
{
	struct seqno_fence *f = to_seqno_fence(fence);

	dma_buf_put(f->sync_buf);
	if (f->ops->release)
		f->ops->release(fence);
	else
		dma_fence_free(&f->base);
}