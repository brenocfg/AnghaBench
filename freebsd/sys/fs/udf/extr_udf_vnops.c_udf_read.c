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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ u_int ;
struct vop_read_args {int a_ioflag; struct uio* a_uio; struct vnode* a_vp; } ;
struct vnode {TYPE_1__* v_mount; } ;
struct uio {scalar_t__ uio_resid; scalar_t__ uio_offset; } ;
struct udf_node {struct udf_mnt* udfmp; struct file_entry* fentry; } ;
struct udf_mnt {long bsize; } ;
struct file_entry {int /*<<< orphan*/  inf_len; int /*<<< orphan*/  l_ad; int /*<<< orphan*/  l_ea; int /*<<< orphan*/ * data; } ;
struct buf {scalar_t__ b_resid; int /*<<< orphan*/ * b_data; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;
typedef  scalar_t__ daddr_t ;
struct TYPE_2__ {int mnt_flag; } ;

/* Variables and functions */
 int EINVAL ; 
 int MNT_NOCLUSTERR ; 
 int /*<<< orphan*/  NOCRED ; 
 struct udf_node* VTON (struct vnode*) ; 
 long blkoff (struct udf_mnt*,int) ; 
 int bread (struct vnode*,scalar_t__,long,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int cluster_read (struct vnode*,scalar_t__,scalar_t__,long,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,struct buf**) ; 
 scalar_t__ is_data_in_fentry (struct udf_node*) ; 
 scalar_t__ lblkno (struct udf_mnt*,int) ; 
 scalar_t__ lblktosize (struct udf_mnt*,scalar_t__) ; 
 size_t le32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ le64toh (int /*<<< orphan*/ ) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int uiomove (int /*<<< orphan*/ *,int,struct uio*) ; 

__attribute__((used)) static int
udf_read(struct vop_read_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct uio *uio = ap->a_uio;
	struct udf_node *node = VTON(vp);
	struct udf_mnt *udfmp;
	struct file_entry *fentry;
	struct buf *bp;
	uint8_t *data;
	daddr_t lbn, rablock;
	off_t diff, fsize;
	ssize_t n;
	int error = 0;
	long size, on;

	if (uio->uio_resid == 0)
		return (0);
	if (uio->uio_offset < 0)
		return (EINVAL);

	if (is_data_in_fentry(node)) {
		fentry = node->fentry;
		data = &fentry->data[le32toh(fentry->l_ea)];
		fsize = le32toh(fentry->l_ad);

		n = uio->uio_resid;
		diff = fsize - uio->uio_offset;
		if (diff <= 0)
			return (0);
		if (diff < n)
			n = diff;
		error = uiomove(data + uio->uio_offset, (int)n, uio);
		return (error);
	}

	fsize = le64toh(node->fentry->inf_len);
	udfmp = node->udfmp;
	do {
		lbn = lblkno(udfmp, uio->uio_offset);
		on = blkoff(udfmp, uio->uio_offset);
		n = min((u_int)(udfmp->bsize - on),
			uio->uio_resid);
		diff = fsize - uio->uio_offset;
		if (diff <= 0)
			return (0);
		if (diff < n)
			n = diff;
		size = udfmp->bsize;
		rablock = lbn + 1;
		if ((vp->v_mount->mnt_flag & MNT_NOCLUSTERR) == 0) {
			if (lblktosize(udfmp, rablock) < fsize) {
				error = cluster_read(vp, fsize, lbn, size,
				    NOCRED, uio->uio_resid,
				    (ap->a_ioflag >> 16), 0, &bp);
			} else {
				error = bread(vp, lbn, size, NOCRED, &bp);
			}
		} else {
			error = bread(vp, lbn, size, NOCRED, &bp);
		}
		if (error != 0) {
			brelse(bp);
			return (error);
		}
		n = min(n, size - bp->b_resid);

		error = uiomove(bp->b_data + on, (int)n, uio);
		brelse(bp);
	} while (error == 0 && uio->uio_resid > 0 && n != 0);
	return (error);
}