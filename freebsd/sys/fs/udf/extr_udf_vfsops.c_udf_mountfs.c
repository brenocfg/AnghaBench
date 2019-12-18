#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct bufobj {int dummy; } ;
struct vnode {struct cdev* v_rdev; struct bufobj v_bufobj; } ;
struct TYPE_13__ {int /*<<< orphan*/  lb_num; } ;
struct TYPE_18__ {int /*<<< orphan*/  len; int /*<<< orphan*/  loc; } ;
struct anchor_vdp {int /*<<< orphan*/  len; TYPE_4__ loc; TYPE_9__ main_vds_ex; } ;
struct udf_mnt {int bsize; int bmask; int part_len; int part_start; struct anchor_vdp root_icb; scalar_t__ bshift; int /*<<< orphan*/ * im_l2d; struct bufobj* im_bo; struct g_consumer* im_cp; int /*<<< orphan*/ * im_d2l; struct vnode* im_devvp; struct cdev* im_dev; struct mount* im_mountp; } ;
struct desc_tag {int dummy; } ;
struct part_desc {int /*<<< orphan*/  start_loc; int /*<<< orphan*/  part_len; int /*<<< orphan*/  part_num; struct desc_tag tag; } ;
struct TYPE_14__ {int /*<<< orphan*/ * val; } ;
struct TYPE_15__ {TYPE_5__ f_fsid; } ;
struct mount {scalar_t__ mnt_iosize_max; int mnt_kern_flag; int /*<<< orphan*/  mnt_flag; TYPE_7__* mnt_vfc; TYPE_6__ mnt_stat; struct udf_mnt* mnt_data; } ;
struct long_ad {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  lb_num; int /*<<< orphan*/  part_num; } ;
struct TYPE_11__ {TYPE_1__ loc; } ;
struct TYPE_12__ {TYPE_2__ fsd_loc; } ;
struct logvol_desc {TYPE_3__ _lvd_use; int /*<<< orphan*/  lb_size; struct desc_tag tag; } ;
struct g_consumer {TYPE_8__* provider; } ;
struct fileset_desc {int /*<<< orphan*/  rootdir_icb; struct desc_tag tag; } ;
struct file_entry {struct desc_tag tag; } ;
struct cdev {scalar_t__ si_iosize_max; } ;
struct buf {int /*<<< orphan*/ * b_data; } ;
struct TYPE_17__ {int sectorsize; } ;
struct TYPE_16__ {int /*<<< orphan*/  vfc_typenum; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ MAXPHYS ; 
 int MNTK_EXTENDED_SHARED ; 
 int MNTK_LOOKUP_SHARED ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_LOCAL ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_UDFMOUNT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NOCRED ; 
 int RDSECTOR (struct vnode*,int,int,struct buf**) ; 
 int /*<<< orphan*/  TAGID_ANCHOR ; 
 int /*<<< orphan*/  TAGID_FENTRY ; 
 int /*<<< orphan*/  TAGID_FSD ; 
 int /*<<< orphan*/  TAGID_LOGVOL ; 
 int /*<<< orphan*/  TAGID_PARTITION ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,struct anchor_vdp*,int) ; 
 int bread (struct vnode*,int,int,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int btodb (int) ; 
 int /*<<< orphan*/  dev2udev (struct cdev*) ; 
 int /*<<< orphan*/  dev_ref (struct cdev*) ; 
 int /*<<< orphan*/  dev_rel (struct cdev*) ; 
 scalar_t__ ffs (int) ; 
 int /*<<< orphan*/  free (struct udf_mnt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  g_vfs_close (struct g_consumer*) ; 
 int g_vfs_open (struct vnode*,struct g_consumer**,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ le16toh (int /*<<< orphan*/ ) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 struct udf_mnt* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int udf_checktag (struct desc_tag*,int /*<<< orphan*/ ) ; 
 scalar_t__ udf_find_partmaps (struct udf_mnt*,struct logvol_desc*) ; 
 int udf_readdevblks (struct udf_mnt*,int,int,struct buf**) ; 

__attribute__((used)) static int
udf_mountfs(struct vnode *devvp, struct mount *mp)
{
	struct buf *bp = NULL;
	struct cdev *dev;
	struct anchor_vdp avdp;
	struct udf_mnt *udfmp = NULL;
	struct part_desc *pd;
	struct logvol_desc *lvd;
	struct fileset_desc *fsd;
	struct file_entry *root_fentry;
	uint32_t sector, size, mvds_start, mvds_end;
	uint32_t logical_secsize;
	uint32_t fsd_offset = 0;
	uint16_t part_num = 0, fsd_part = 0;
	int error = EINVAL;
	int logvol_found = 0, part_found = 0, fsd_found = 0;
	int bsize;
	struct g_consumer *cp;
	struct bufobj *bo;

	dev = devvp->v_rdev;
	dev_ref(dev);
	g_topology_lock();
	error = g_vfs_open(devvp, &cp, "udf", 0);
	g_topology_unlock();
	VOP_UNLOCK(devvp, 0);
	if (error)
		goto bail;

	bo = &devvp->v_bufobj;

	if (devvp->v_rdev->si_iosize_max != 0)
		mp->mnt_iosize_max = devvp->v_rdev->si_iosize_max;
	if (mp->mnt_iosize_max > MAXPHYS)
		mp->mnt_iosize_max = MAXPHYS;

	/* XXX: should be M_WAITOK */
	udfmp = malloc(sizeof(struct udf_mnt), M_UDFMOUNT,
	    M_NOWAIT | M_ZERO);
	if (udfmp == NULL) {
		printf("Cannot allocate UDF mount struct\n");
		error = ENOMEM;
		goto bail;
	}

	mp->mnt_data = udfmp;
	mp->mnt_stat.f_fsid.val[0] = dev2udev(devvp->v_rdev);
	mp->mnt_stat.f_fsid.val[1] = mp->mnt_vfc->vfc_typenum;
	MNT_ILOCK(mp);
	mp->mnt_flag |= MNT_LOCAL;
	mp->mnt_kern_flag |= MNTK_LOOKUP_SHARED | MNTK_EXTENDED_SHARED;
	MNT_IUNLOCK(mp);
	udfmp->im_mountp = mp;
	udfmp->im_dev = dev;
	udfmp->im_devvp = devvp;
	udfmp->im_d2l = NULL;
	udfmp->im_cp = cp;
	udfmp->im_bo = bo;

#if 0
	udfmp->im_l2d = NULL;
#endif
	/*
	 * The UDF specification defines a logical sectorsize of 2048
	 * for DVD media.
	 */
	logical_secsize = 2048;

	if (((logical_secsize % cp->provider->sectorsize) != 0) ||
	    (logical_secsize < cp->provider->sectorsize)) {
		error = EINVAL;
		goto bail;
	}

	bsize = cp->provider->sectorsize;

	/* 
	 * Get the Anchor Volume Descriptor Pointer from sector 256.
	 * XXX Should also check sector n - 256, n, and 512.
	 */
	sector = 256;
	if ((error = bread(devvp, sector * btodb(logical_secsize), bsize,
			   NOCRED, &bp)) != 0)
		goto bail;
	if ((error = udf_checktag((struct desc_tag *)bp->b_data, TAGID_ANCHOR)))
		goto bail;

	bcopy(bp->b_data, &avdp, sizeof(struct anchor_vdp));
	brelse(bp);
	bp = NULL;

	/*
	 * Extract the Partition Descriptor and Logical Volume Descriptor
	 * from the Volume Descriptor Sequence.
	 * XXX Should we care about the partition type right now?
	 * XXX What about multiple partitions?
	 */
	mvds_start = le32toh(avdp.main_vds_ex.loc);
	mvds_end = mvds_start + (le32toh(avdp.main_vds_ex.len) - 1) / bsize;
	for (sector = mvds_start; sector < mvds_end; sector++) {
		if ((error = bread(devvp, sector * btodb(logical_secsize),
				   bsize, NOCRED, &bp)) != 0) {
			printf("Can't read sector %d of VDS\n", sector);
			goto bail;
		}
		lvd = (struct logvol_desc *)bp->b_data;
		if (!udf_checktag(&lvd->tag, TAGID_LOGVOL)) {
			udfmp->bsize = le32toh(lvd->lb_size);
			udfmp->bmask = udfmp->bsize - 1;
			udfmp->bshift = ffs(udfmp->bsize) - 1;
			fsd_part = le16toh(lvd->_lvd_use.fsd_loc.loc.part_num);
			fsd_offset = le32toh(lvd->_lvd_use.fsd_loc.loc.lb_num);
			if (udf_find_partmaps(udfmp, lvd))
				break;
			logvol_found = 1;
		}
		pd = (struct part_desc *)bp->b_data;
		if (!udf_checktag(&pd->tag, TAGID_PARTITION)) {
			part_found = 1;
			part_num = le16toh(pd->part_num);
			udfmp->part_len = le32toh(pd->part_len);
			udfmp->part_start = le32toh(pd->start_loc);
		}

		brelse(bp); 
		bp = NULL;
		if ((part_found) && (logvol_found))
			break;
	}

	if (!part_found || !logvol_found) {
		error = EINVAL;
		goto bail;
	}

	if (fsd_part != part_num) {
		printf("FSD does not lie within the partition!\n");
		error = EINVAL;
		goto bail;
	}


	/*
	 * Grab the Fileset Descriptor
	 * Thanks to Chuck McCrobie <mccrobie@cablespeed.com> for pointing
	 * me in the right direction here.
	 */
	sector = udfmp->part_start + fsd_offset;
	if ((error = RDSECTOR(devvp, sector, udfmp->bsize, &bp)) != 0) {
		printf("Cannot read sector %d of FSD\n", sector);
		goto bail;
	}
	fsd = (struct fileset_desc *)bp->b_data;
	if (!udf_checktag(&fsd->tag, TAGID_FSD)) {
		fsd_found = 1;
		bcopy(&fsd->rootdir_icb, &udfmp->root_icb,
		    sizeof(struct long_ad));
	}

	brelse(bp);
	bp = NULL;

	if (!fsd_found) {
		printf("Couldn't find the fsd\n");
		error = EINVAL;
		goto bail;
	}

	/*
	 * Find the file entry for the root directory.
	 */
	sector = le32toh(udfmp->root_icb.loc.lb_num) + udfmp->part_start;
	size = le32toh(udfmp->root_icb.len);
	if ((error = udf_readdevblks(udfmp, sector, size, &bp)) != 0) {
		printf("Cannot read sector %d\n", sector);
		goto bail;
	}

	root_fentry = (struct file_entry *)bp->b_data;
	if ((error = udf_checktag(&root_fentry->tag, TAGID_FENTRY))) {
		printf("Invalid root file entry!\n");
		goto bail;
	}

	brelse(bp);
	bp = NULL;

	return 0;

bail:
	if (udfmp != NULL)
		free(udfmp, M_UDFMOUNT);
	if (bp != NULL)
		brelse(bp);
	if (cp != NULL) {
		g_topology_lock();
		g_vfs_close(cp);
		g_topology_unlock();
	}
	dev_rel(dev);
	return error;
}