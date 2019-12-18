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
struct virtio_blk_outhdr {int /*<<< orphan*/  sector; int /*<<< orphan*/  type; } ;
typedef  struct virtio_blk_outhdr uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct vqueue_info {int dummy; } ;
struct iovec {int iov_len; struct virtio_blk_outhdr* iov_base; } ;
struct beri_vtblk_softc {int /*<<< orphan*/  ident; int /*<<< orphan*/  beri_mem_offset; } ;
typedef  int off_t ;

/* Variables and functions */
 int DEV_BSIZE ; 
 int ENOSYS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MIN (int,int) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 struct virtio_blk_outhdr VIRTIO_BLK_S_IOERR ; 
 struct virtio_blk_outhdr VIRTIO_BLK_S_OK ; 
 struct virtio_blk_outhdr VIRTIO_BLK_S_UNSUPP ; 
 int VIRTIO_BLK_T_BARRIER ; 
#define  VIRTIO_BLK_T_FLUSH 131 
#define  VIRTIO_BLK_T_GET_ID 130 
#define  VIRTIO_BLK_T_IN 129 
#define  VIRTIO_BLK_T_OUT 128 
 int VTBLK_MAXSEGS ; 
 int be32toh (int /*<<< orphan*/ ) ; 
 int be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct iovec*,int /*<<< orphan*/ ) ; 
 struct iovec* getcopy (struct iovec*,int) ; 
 int /*<<< orphan*/  strncpy (struct virtio_blk_outhdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vq_getchain (int /*<<< orphan*/ ,struct vqueue_info*,struct iovec*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vq_relchain (struct vqueue_info*,struct iovec*,int,int) ; 
 int vtblk_rdwr (struct beri_vtblk_softc*,struct iovec*,int,int,int,int) ; 

__attribute__((used)) static void
vtblk_proc(struct beri_vtblk_softc *sc, struct vqueue_info *vq)
{
	struct iovec iov[VTBLK_MAXSEGS + 2];
	uint16_t flags[VTBLK_MAXSEGS + 2];
	struct virtio_blk_outhdr *vbh;
	struct iovec *tiov;
	uint8_t *status;
	off_t offset;
	int iolen;
	int type;
	int i, n;
	int err;

	n = vq_getchain(sc->beri_mem_offset, vq, iov,
		VTBLK_MAXSEGS + 2, flags);
	KASSERT(n >= 2 && n <= VTBLK_MAXSEGS + 2,
		("wrong n value %d", n));

	tiov = getcopy(iov, n);
	vbh = iov[0].iov_base;

	status = iov[n-1].iov_base;
	KASSERT(iov[n-1].iov_len == 1,
		("iov_len == %d", iov[n-1].iov_len));

	type = be32toh(vbh->type) & ~VIRTIO_BLK_T_BARRIER;
	offset = be64toh(vbh->sector) * DEV_BSIZE;

	iolen = 0;
	for (i = 1; i < (n-1); i++) {
		iolen += iov[i].iov_len;
	}

	switch (type) {
	case VIRTIO_BLK_T_OUT:
	case VIRTIO_BLK_T_IN:
		err = vtblk_rdwr(sc, tiov + 1, i - 1,
			offset, type, iolen);
		break;
	case VIRTIO_BLK_T_GET_ID:
		/* Assume a single buffer */
		strncpy(iov[1].iov_base, sc->ident,
		    MIN(iov[1].iov_len, sizeof(sc->ident)));
		err = 0;
		break;
	case VIRTIO_BLK_T_FLUSH:
		/* Possible? */
	default:
		err = -ENOSYS;
		break;
	}

	if (err < 0) {
		if (err == -ENOSYS) {
			*status = VIRTIO_BLK_S_UNSUPP;
		} else
			*status = VIRTIO_BLK_S_IOERR;
	} else
		*status = VIRTIO_BLK_S_OK;

	free(tiov, M_DEVBUF);
	vq_relchain(vq, iov, n, 1);
}