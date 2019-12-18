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
struct vqueue_info {int /*<<< orphan*/  vq_next_used; TYPE_1__* vq_used; } ;
struct TYPE_2__ {int /*<<< orphan*/  vu_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_thread_fence_rel () ; 

void
vq_relchain_publish(struct vqueue_info *vq)
{
	/*
	 * Ensure the used descriptor is visible before updating the index.
	 * This is necessary on ISAs with memory ordering less strict than x86
	 * (and even on x86 to act as a compiler barrier).
	 */
	atomic_thread_fence_rel();
	vq->vq_used->vu_idx = vq->vq_next_used;
}