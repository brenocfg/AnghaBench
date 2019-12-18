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
struct vqueue_info {scalar_t__ vq_last_avail; TYPE_1__* vq_avail; } ;
struct TYPE_2__ {scalar_t__ va_idx; } ;

/* Variables and functions */
 scalar_t__ vq_ring_ready (struct vqueue_info*) ; 

__attribute__((used)) static inline int
vq_has_descs(struct vqueue_info *vq)
{

	return (vq_ring_ready(vq) && vq->vq_last_avail !=
	    vq->vq_avail->va_idx);
}