#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vqueue_info {int vq_flags; } ;

/* Variables and functions */
 int VQ_ALLOC ; 

int
vq_ring_ready(struct vqueue_info *vq)
{

	return (vq->vq_flags & VQ_ALLOC);
}