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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct vring_used {int dummy; } ;
struct vring_desc {int dummy; } ;
struct vring_avail {int dummy; } ;
struct vqueue_info {int vq_qsize; int vq_pfn; scalar_t__ vq_last_avail; int /*<<< orphan*/  vq_flags; struct vring_used* vq_used; struct vring_avail* vq_avail; struct vring_desc* vq_desc; } ;
struct beri_vtblk_softc {int /*<<< orphan*/  beri_mem_offset; struct vqueue_info* vs_queues; } ;

/* Variables and functions */
 int NUM_DESCS ; 
 int PAGE_SHIFT ; 
 int READ4 (struct beri_vtblk_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIRTIO_MMIO_QUEUE_PFN ; 
 int /*<<< orphan*/  VQ_ALLOC ; 
 int /*<<< orphan*/  VRING_ALIGN ; 
 int be32toh (int) ; 
 int /*<<< orphan*/ * paddr_map (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ roundup2 (uintptr_t,int /*<<< orphan*/ ) ; 
 int vring_size (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vq_init(struct beri_vtblk_softc *sc)
{
	struct vqueue_info *vq;
	uint8_t *base;
	int size;
	int reg;
	int pfn;

	vq = &sc->vs_queues[0];
	vq->vq_qsize = NUM_DESCS;

	reg = READ4(sc, VIRTIO_MMIO_QUEUE_PFN);
	pfn = be32toh(reg);
	vq->vq_pfn = pfn;

	size = vring_size(vq->vq_qsize, VRING_ALIGN);
	base = paddr_map(sc->beri_mem_offset,
		(pfn << PAGE_SHIFT), size);

	/* First pages are descriptors */
	vq->vq_desc = (struct vring_desc *)base;
	base += vq->vq_qsize * sizeof(struct vring_desc);

	/* Then avail ring */
	vq->vq_avail = (struct vring_avail *)base;
	base += (2 + vq->vq_qsize + 1) * sizeof(uint16_t);

	/* Then it's rounded up to the next page */
	base = (uint8_t *)roundup2((uintptr_t)base, VRING_ALIGN);

	/* And the last pages are the used ring */
	vq->vq_used = (struct vring_used *)base;

	/* Mark queue as allocated, and start at 0 when we use it. */
	vq->vq_flags = VQ_ALLOC;
	vq->vq_last_avail = 0;

	return (0);
}