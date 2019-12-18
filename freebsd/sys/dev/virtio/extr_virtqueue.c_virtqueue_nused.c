#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {TYPE_1__* used; } ;
struct virtqueue {scalar_t__ vq_used_cons_idx; scalar_t__ vq_nentries; TYPE_2__ vq_ring; } ;
struct TYPE_3__ {scalar_t__ idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  VQASSERT (struct virtqueue*,int,char*) ; 

int
virtqueue_nused(struct virtqueue *vq)
{
	uint16_t used_idx, nused;

	used_idx = vq->vq_ring.used->idx;

	nused = (uint16_t)(used_idx - vq->vq_used_cons_idx);
	VQASSERT(vq, nused <= vq->vq_nentries, "used more than available");

	return (nused);
}