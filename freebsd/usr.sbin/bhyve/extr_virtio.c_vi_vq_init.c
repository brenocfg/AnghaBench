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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct vring_used {int dummy; } ;
struct vring_avail {int dummy; } ;
struct vqueue_info {int vq_qsize; scalar_t__ vq_save_used; scalar_t__ vq_next_used; scalar_t__ vq_last_avail; int /*<<< orphan*/  vq_flags; struct vring_used* vq_used; struct vring_avail* vq_avail; struct virtio_desc* vq_desc; scalar_t__ vq_pfn; } ;
struct virtio_softc {size_t vs_curq; TYPE_1__* vs_pi; struct vqueue_info* vs_queues; } ;
struct virtio_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pi_vmctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  VQ_ALLOC ; 
 int /*<<< orphan*/  VRING_ALIGN ; 
 int VRING_PFN ; 
 char* paddr_guest2host (int /*<<< orphan*/ ,int,size_t) ; 
 scalar_t__ roundup2 (uintptr_t,int /*<<< orphan*/ ) ; 
 size_t vring_size (int) ; 

void
vi_vq_init(struct virtio_softc *vs, uint32_t pfn)
{
	struct vqueue_info *vq;
	uint64_t phys;
	size_t size;
	char *base;

	vq = &vs->vs_queues[vs->vs_curq];
	vq->vq_pfn = pfn;
	phys = (uint64_t)pfn << VRING_PFN;
	size = vring_size(vq->vq_qsize);
	base = paddr_guest2host(vs->vs_pi->pi_vmctx, phys, size);

	/* First page(s) are descriptors... */
	vq->vq_desc = (struct virtio_desc *)base;
	base += vq->vq_qsize * sizeof(struct virtio_desc);

	/* ... immediately followed by "avail" ring (entirely uint16_t's) */
	vq->vq_avail = (struct vring_avail *)base;
	base += (2 + vq->vq_qsize + 1) * sizeof(uint16_t);

	/* Then it's rounded up to the next page... */
	base = (char *)roundup2((uintptr_t)base, VRING_ALIGN);

	/* ... and the last page(s) are the used ring. */
	vq->vq_used = (struct vring_used *)base;

	/* Mark queue as allocated, and start at 0 when we use it. */
	vq->vq_flags = VQ_ALLOC;
	vq->vq_last_avail = 0;
	vq->vq_next_used = 0;
	vq->vq_save_used = 0;
}