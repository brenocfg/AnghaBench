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
struct vtbe_softc {int hdrsize; int /*<<< orphan*/  pio_send; int /*<<< orphan*/  beri_mem_offset; struct ifnet* ifp; struct vqueue_info* vs_queues; } ;
struct vqueue_info {TYPE_1__* vq_used; int /*<<< orphan*/  vq_save_used; } ;
struct virtio_net_hdr {int dummy; } ;
struct uio {int uio_resid; int uio_iovcnt; int /*<<< orphan*/  uio_rw; scalar_t__ uio_offset; int /*<<< orphan*/  uio_segflg; struct iovec* uio_iov; } ;
struct mbuf {int dummy; } ;
struct iovec {int iov_len; struct virtio_net_hdr* iov_base; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; } ;
struct TYPE_2__ {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int DESC_COUNT ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  PIO_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Q_INTR ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  VIRTIO_MMIO_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  VIRTIO_MMIO_INT_VRING ; 
 int /*<<< orphan*/  VTBE_ASSERT_LOCKED (struct vtbe_softc*) ; 
 int /*<<< orphan*/  WRITE4 (struct vtbe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  be16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct iovec*,int /*<<< orphan*/ ) ; 
 struct iovec* getcopy (struct iovec*,int) ; 
 int htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int m_mbuftouio (struct uio*,struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct virtio_net_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int vq_getchain (int /*<<< orphan*/ ,struct vqueue_info*,struct iovec*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vq_has_descs (struct vqueue_info*) ; 
 int /*<<< orphan*/  vq_relchain (struct vqueue_info*,struct iovec*,int,int) ; 
 int /*<<< orphan*/  vq_ring_ready (struct vqueue_info*) ; 

__attribute__((used)) static void
vtbe_txstart_locked(struct vtbe_softc *sc)
{
	struct iovec iov[DESC_COUNT];
	struct virtio_net_hdr *vnh;
	struct vqueue_info *vq;
	struct iovec *tiov;
	struct ifnet *ifp;
	struct mbuf *m;
	struct uio uio;
	int enqueued;
	int iolen;
	int error;
	int reg;
	int len;
	int n;

	VTBE_ASSERT_LOCKED(sc);

	/* RX queue */
	vq = &sc->vs_queues[0];
	if (!vq_has_descs(vq)) {
		return;
	}

	ifp = sc->ifp;
	if (ifp->if_drv_flags & IFF_DRV_OACTIVE) {
		return;
	}

	enqueued = 0;

	if (!vq_ring_ready(vq))
		return;

	vq->vq_save_used = be16toh(vq->vq_used->idx);

	for (;;) {
		if (!vq_has_descs(vq)) {
			ifp->if_drv_flags |= IFF_DRV_OACTIVE;
			break;
		}

		IFQ_DRV_DEQUEUE(&ifp->if_snd, m);
		if (m == NULL) {
			break;
		}

		n = vq_getchain(sc->beri_mem_offset, vq, iov,
			DESC_COUNT, NULL);
		KASSERT(n == 2,
			("Unexpected amount of descriptors (%d)", n));

		tiov = getcopy(iov, n);
		vnh = iov[0].iov_base;
		memset(vnh, 0, sc->hdrsize);

		len = iov[1].iov_len;
		uio.uio_resid = len;
		uio.uio_iov = &tiov[1];
		uio.uio_segflg = UIO_SYSSPACE;
		uio.uio_iovcnt = 1;
		uio.uio_offset = 0;
		uio.uio_rw = UIO_READ;

		error = m_mbuftouio(&uio, m, 0);
		if (error)
			panic("m_mbuftouio failed\n");

		iolen = (len - uio.uio_resid + sc->hdrsize);

		free(tiov, M_DEVBUF);
		vq_relchain(vq, iov, n, iolen);

		if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);

		BPF_MTAP(ifp, m);
		m_freem(m);

		++enqueued;
	}

	if (enqueued != 0) {
		reg = htobe32(VIRTIO_MMIO_INT_VRING);
		WRITE4(sc, VIRTIO_MMIO_INTERRUPT_STATUS, reg);

		PIO_SET(sc->pio_send, Q_INTR, 1);
	}
}