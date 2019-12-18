#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct vqueue_info {int dummy; } ;
struct virtio_blk_hdr {int vbh_sector; int vbh_type; } ;
struct pci_vtblk_softc {int /*<<< orphan*/  vbsc_ident; int /*<<< orphan*/  bc; struct pci_vtblk_ioreq* vbsc_ios; } ;
struct TYPE_5__ {int br_iovcnt; int br_offset; scalar_t__ br_resid; int /*<<< orphan*/  br_iov; } ;
struct pci_vtblk_ioreq {TYPE_1__ io_req; struct virtio_blk_hdr* io_status; } ;
struct iovec {int iov_len; struct virtio_blk_hdr* iov_base; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int BLOCKIF_IOV_MAX ; 
 int DEV_BSIZE ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  MIN (int,int) ; 
 int VBH_FLAG_BARRIER ; 
#define  VBH_OP_FLUSH 132 
#define  VBH_OP_FLUSH_OUT 131 
#define  VBH_OP_IDENT 130 
#define  VBH_OP_READ 129 
#define  VBH_OP_WRITE 128 
 size_t VRING_DESC_F_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int blockif_flush (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int blockif_read (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int blockif_write (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct iovec*,int) ; 
 int /*<<< orphan*/  memset (struct virtio_blk_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_vtblk_done (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (struct virtio_blk_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vq_getchain (struct vqueue_info*,size_t*,struct iovec*,int,size_t*) ; 

__attribute__((used)) static void
pci_vtblk_proc(struct pci_vtblk_softc *sc, struct vqueue_info *vq)
{
	struct virtio_blk_hdr *vbh;
	struct pci_vtblk_ioreq *io;
	int i, n;
	int err;
	ssize_t iolen;
	int writeop, type;
	struct iovec iov[BLOCKIF_IOV_MAX + 2];
	uint16_t idx, flags[BLOCKIF_IOV_MAX + 2];

	n = vq_getchain(vq, &idx, iov, BLOCKIF_IOV_MAX + 2, flags);

	/*
	 * The first descriptor will be the read-only fixed header,
	 * and the last is for status (hence +2 above and below).
	 * The remaining iov's are the actual data I/O vectors.
	 *
	 * XXX - note - this fails on crash dump, which does a
	 * VIRTIO_BLK_T_FLUSH with a zero transfer length
	 */
	assert(n >= 2 && n <= BLOCKIF_IOV_MAX + 2);

	io = &sc->vbsc_ios[idx];
	assert((flags[0] & VRING_DESC_F_WRITE) == 0);
	assert(iov[0].iov_len == sizeof(struct virtio_blk_hdr));
	vbh = iov[0].iov_base;
	memcpy(&io->io_req.br_iov, &iov[1], sizeof(struct iovec) * (n - 2));
	io->io_req.br_iovcnt = n - 2;
	io->io_req.br_offset = vbh->vbh_sector * DEV_BSIZE;
	io->io_status = iov[--n].iov_base;
	assert(iov[n].iov_len == 1);
	assert(flags[n] & VRING_DESC_F_WRITE);

	/*
	 * XXX
	 * The guest should not be setting the BARRIER flag because
	 * we don't advertise the capability.
	 */
	type = vbh->vbh_type & ~VBH_FLAG_BARRIER;
	writeop = (type == VBH_OP_WRITE);

	iolen = 0;
	for (i = 1; i < n; i++) {
		/*
		 * - write op implies read-only descriptor,
		 * - read/ident op implies write-only descriptor,
		 * therefore test the inverse of the descriptor bit
		 * to the op.
		 */
		assert(((flags[i] & VRING_DESC_F_WRITE) == 0) == writeop);
		iolen += iov[i].iov_len;
	}
	io->io_req.br_resid = iolen;

	DPRINTF(("virtio-block: %s op, %zd bytes, %d segs, offset %ld\n\r",
		 writeop ? "write" : "read/ident", iolen, i - 1,
		 io->io_req.br_offset));

	switch (type) {
	case VBH_OP_READ:
		err = blockif_read(sc->bc, &io->io_req);
		break;
	case VBH_OP_WRITE:
		err = blockif_write(sc->bc, &io->io_req);
		break;
	case VBH_OP_FLUSH:
	case VBH_OP_FLUSH_OUT:
		err = blockif_flush(sc->bc, &io->io_req);
		break;
	case VBH_OP_IDENT:
		/* Assume a single buffer */
		/* S/n equal to buffer is not zero-terminated. */
		memset(iov[1].iov_base, 0, iov[1].iov_len);
		strncpy(iov[1].iov_base, sc->vbsc_ident,
		    MIN(iov[1].iov_len, sizeof(sc->vbsc_ident)));
		pci_vtblk_done(&io->io_req, 0);
		return;
	default:
		pci_vtblk_done(&io->io_req, EOPNOTSUPP);
		return;
	}
	assert(err == 0);
}