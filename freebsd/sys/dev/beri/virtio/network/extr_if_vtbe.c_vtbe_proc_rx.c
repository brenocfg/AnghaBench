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
struct vtbe_softc {scalar_t__ hdrsize; int /*<<< orphan*/  beri_mem_offset; struct ifnet* ifp; } ;
struct vqueue_info {int dummy; } ;
struct uio {int uio_resid; int uio_iovcnt; int /*<<< orphan*/  uio_rw; int /*<<< orphan*/  uio_segflg; struct iovec* uio_iov; } ;
struct TYPE_2__ {struct ifnet* rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct iovec {scalar_t__ iov_len; } ;
struct ifnet {int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;int /*<<< orphan*/  if_vnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int DESC_COUNT ; 
 int /*<<< orphan*/  ETHER_ALIGN ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int /*<<< orphan*/  VTBE_LOCK (struct vtbe_softc*) ; 
 int /*<<< orphan*/  VTBE_UNLOCK (struct vtbe_softc*) ; 
 int /*<<< orphan*/  free (struct iovec*,int /*<<< orphan*/ ) ; 
 struct iovec* getcopy (struct iovec*,int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 struct mbuf* m_uiotombuf (struct uio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 
 int vq_getchain (int /*<<< orphan*/ ,struct vqueue_info*,struct iovec*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vq_relchain (struct vqueue_info*,struct iovec*,int,scalar_t__) ; 

__attribute__((used)) static void
vtbe_proc_rx(struct vtbe_softc *sc, struct vqueue_info *vq)
{
	struct iovec iov[DESC_COUNT];
	struct iovec *tiov;
	struct ifnet *ifp;
	struct uio uio;
	struct mbuf *m;
	int iolen;
	int i;
	int n;

	ifp = sc->ifp;

	n = vq_getchain(sc->beri_mem_offset, vq, iov,
		DESC_COUNT, NULL);

	KASSERT(n >= 1 && n <= DESC_COUNT,
		("wrong n %d", n));

	tiov = getcopy(iov, n);

	iolen = 0;
	for (i = 1; i < n; i++) {
		iolen += iov[i].iov_len;
	}

	uio.uio_resid = iolen;
	uio.uio_iov = &tiov[1];
	uio.uio_segflg = UIO_SYSSPACE;
	uio.uio_iovcnt = (n - 1);
	uio.uio_rw = UIO_WRITE;

	if ((m = m_uiotombuf(&uio, M_NOWAIT, 0, ETHER_ALIGN,
	    M_PKTHDR)) == NULL) {
		if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
		goto done;
	}

	m->m_pkthdr.rcvif = ifp;

	if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);

	CURVNET_SET(ifp->if_vnet);
	VTBE_UNLOCK(sc);
	(*ifp->if_input)(ifp, m);
	VTBE_LOCK(sc);
	CURVNET_RESTORE();

done:
	free(tiov, M_DEVBUF);
	vq_relchain(vq, iov, n, iolen + sc->hdrsize);
}