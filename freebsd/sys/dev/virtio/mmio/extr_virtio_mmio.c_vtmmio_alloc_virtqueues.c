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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct vtmmio_virtqueue {int /*<<< orphan*/  vtv_no_intr; struct virtqueue* vtv_vq; } ;
struct vtmmio_softc {scalar_t__ vtmmio_nvqs; struct vtmmio_virtqueue* vtmmio_vqs; } ;
struct vq_alloc_info {int /*<<< orphan*/ * vqai_intr; struct virtqueue** vqai_vq; } ;
struct virtqueue {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EALREADY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  VIRTIO_MMIO_GUEST_PAGE_SIZE ; 
 int /*<<< orphan*/  VIRTIO_MMIO_QUEUE_ALIGN ; 
 int /*<<< orphan*/  VIRTIO_MMIO_QUEUE_NUM ; 
 int /*<<< orphan*/  VIRTIO_MMIO_QUEUE_NUM_MAX ; 
 int /*<<< orphan*/  VIRTIO_MMIO_QUEUE_PFN ; 
 int /*<<< orphan*/  VIRTIO_MMIO_QUEUE_SEL ; 
 int VIRTIO_MMIO_VRING_ALIGN ; 
 struct vtmmio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 struct vtmmio_virtqueue* malloc (int,int /*<<< orphan*/ ,int) ; 
 int virtqueue_alloc (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,struct vq_alloc_info*,struct virtqueue**) ; 
 int virtqueue_paddr (struct virtqueue*) ; 
 int /*<<< orphan*/  vtmmio_free_virtqueues (struct vtmmio_softc*) ; 
 int vtmmio_read_config_4 (struct vtmmio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtmmio_select_virtqueue (struct vtmmio_softc*,int) ; 
 int /*<<< orphan*/  vtmmio_write_config_4 (struct vtmmio_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
vtmmio_alloc_virtqueues(device_t dev, int flags, int nvqs,
    struct vq_alloc_info *vq_info)
{
	struct vtmmio_virtqueue *vqx;
	struct vq_alloc_info *info;
	struct vtmmio_softc *sc;
	struct virtqueue *vq;
	uint32_t size;
	int idx, error;

	sc = device_get_softc(dev);

	if (sc->vtmmio_nvqs != 0)
		return (EALREADY);
	if (nvqs <= 0)
		return (EINVAL);

	sc->vtmmio_vqs = malloc(nvqs * sizeof(struct vtmmio_virtqueue),
	    M_DEVBUF, M_NOWAIT | M_ZERO);
	if (sc->vtmmio_vqs == NULL)
		return (ENOMEM);

	vtmmio_write_config_4(sc, VIRTIO_MMIO_GUEST_PAGE_SIZE,
	    (1 << PAGE_SHIFT));

	for (idx = 0; idx < nvqs; idx++) {
		vqx = &sc->vtmmio_vqs[idx];
		info = &vq_info[idx];

		vtmmio_write_config_4(sc, VIRTIO_MMIO_QUEUE_SEL, idx);

		vtmmio_select_virtqueue(sc, idx);
		size = vtmmio_read_config_4(sc, VIRTIO_MMIO_QUEUE_NUM_MAX);

		error = virtqueue_alloc(dev, idx, size,
		    VIRTIO_MMIO_VRING_ALIGN, ~(vm_paddr_t)0, info, &vq);
		if (error) {
			device_printf(dev,
			    "cannot allocate virtqueue %d: %d\n",
			    idx, error);
			break;
		}

		vtmmio_write_config_4(sc, VIRTIO_MMIO_QUEUE_NUM, size);
		vtmmio_write_config_4(sc, VIRTIO_MMIO_QUEUE_ALIGN,
		    VIRTIO_MMIO_VRING_ALIGN);
#if 0
		device_printf(dev, "virtqueue paddr 0x%08lx\n",
		    (uint64_t)virtqueue_paddr(vq));
#endif
		vtmmio_write_config_4(sc, VIRTIO_MMIO_QUEUE_PFN,
		    virtqueue_paddr(vq) >> PAGE_SHIFT);

		vqx->vtv_vq = *info->vqai_vq = vq;
		vqx->vtv_no_intr = info->vqai_intr == NULL;

		sc->vtmmio_nvqs++;
	}

	if (error)
		vtmmio_free_virtqueues(sc);

	return (error);
}