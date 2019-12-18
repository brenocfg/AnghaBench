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
struct vring_desc {int dummy; } ;
struct vq_desc_extra {int /*<<< orphan*/ * indirect; int /*<<< orphan*/  indirect_paddr; } ;
struct virtqueue {int vq_max_indirect_size; int vq_indirect_mem_size; int vq_nentries; struct vq_desc_extra* vq_descx; int /*<<< orphan*/  vq_flags; int /*<<< orphan*/  vq_name; int /*<<< orphan*/  vq_queue_index; int /*<<< orphan*/  vq_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 scalar_t__ VIRTIO_BUS_WITH_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIRTIO_RING_F_INDIRECT_DESC ; 
 int /*<<< orphan*/  VIRTQUEUE_FLAG_INDIRECT ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_init_indirect_list (struct virtqueue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtophys (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
virtqueue_init_indirect(struct virtqueue *vq, int indirect_size)
{
	device_t dev;
	struct vq_desc_extra *dxp;
	int i, size;

	dev = vq->vq_dev;

	if (VIRTIO_BUS_WITH_FEATURE(dev, VIRTIO_RING_F_INDIRECT_DESC) == 0) {
		/*
		 * Indirect descriptors requested by the driver but not
		 * negotiated. Return zero to keep the initialization
		 * going: we'll run fine without.
		 */
		if (bootverbose)
			device_printf(dev, "virtqueue %d (%s) requested "
			    "indirect descriptors but not negotiated\n",
			    vq->vq_queue_index, vq->vq_name);
		return (0);
	}

	size = indirect_size * sizeof(struct vring_desc);
	vq->vq_max_indirect_size = indirect_size;
	vq->vq_indirect_mem_size = size;
	vq->vq_flags |= VIRTQUEUE_FLAG_INDIRECT;

	for (i = 0; i < vq->vq_nentries; i++) {
		dxp = &vq->vq_descx[i];

		dxp->indirect = malloc(size, M_DEVBUF, M_NOWAIT);
		if (dxp->indirect == NULL) {
			device_printf(dev, "cannot allocate indirect list\n");
			return (ENOMEM);
		}

		dxp->indirect_paddr = vtophys(dxp->indirect);
		virtqueue_init_indirect_list(vq, dxp->indirect);
	}

	return (0);
}