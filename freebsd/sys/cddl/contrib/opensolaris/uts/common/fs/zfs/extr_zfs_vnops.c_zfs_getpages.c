#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ z_blksz; int /*<<< orphan*/  z_id; int /*<<< orphan*/  z_rangelock; TYPE_4__* z_zfsvfs; } ;
typedef  TYPE_3__ znode_t ;
struct TYPE_20__ {int /*<<< orphan*/ * z_os; } ;
typedef  TYPE_4__ zfsvfs_t ;
typedef  TYPE_5__* vm_page_t ;
typedef  TYPE_6__* vm_object_t ;
typedef  scalar_t__ uint_t ;
struct vnode {int dummy; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  locked_range_t ;
struct TYPE_17__ {int vnp_size; } ;
struct TYPE_18__ {TYPE_1__ vnp; } ;
struct TYPE_22__ {TYPE_2__ un_pager; } ;
struct TYPE_21__ {int pindex; TYPE_6__* object; } ;

/* Variables and functions */
 int IDX_TO_OFF (int) ; 
 int MIN (int,int) ; 
 int OFF_TO_IDX (int) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  RL_READER ; 
 int /*<<< orphan*/  VM_CNT_ADD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VM_CNT_INC (int /*<<< orphan*/ ) ; 
 TYPE_3__* VTOZ (struct vnode*) ; 
 int /*<<< orphan*/  ZFS_ACCESSTIME_STAMP (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_4__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_4__*) ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_3__*) ; 
 int dmu_read_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__**,int,int*,int*,int) ; 
 int /*<<< orphan*/ * rangelock_enter (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rangelock_exit (int /*<<< orphan*/ *) ; 
 int round_page (int) ; 
 int rounddown (int,scalar_t__) ; 
 int roundup (int,scalar_t__) ; 
 int /*<<< orphan*/  v_vnodein ; 
 int /*<<< orphan*/  v_vnodepgsin ; 
 int zfs_vm_pagerret_bad ; 
 int zfs_vm_pagerret_error ; 
 int zfs_vm_pagerret_ok ; 
 int /*<<< orphan*/  zfs_vmobject_wlock (TYPE_6__*) ; 
 int /*<<< orphan*/  zfs_vmobject_wunlock (TYPE_6__*) ; 

__attribute__((used)) static int
zfs_getpages(struct vnode *vp, vm_page_t *ma, int count, int *rbehind,
    int *rahead)
{
	znode_t *zp = VTOZ(vp);
	zfsvfs_t *zfsvfs = zp->z_zfsvfs;
	objset_t *os = zp->z_zfsvfs->z_os;
	locked_range_t *lr;
	vm_object_t object;
	off_t start, end, obj_size;
	uint_t blksz;
	int pgsin_b, pgsin_a;
	int error;

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(zp);

	start = IDX_TO_OFF(ma[0]->pindex);
	end = IDX_TO_OFF(ma[count - 1]->pindex + 1);

	/*
	 * Lock a range covering all required and optional pages.
	 * Note that we need to handle the case of the block size growing.
	 */
	for (;;) {
		blksz = zp->z_blksz;
		lr = rangelock_enter(&zp->z_rangelock, rounddown(start, blksz),
		    roundup(end, blksz) - rounddown(start, blksz), RL_READER);
		if (blksz == zp->z_blksz)
			break;
		rangelock_exit(lr);
	}

	object = ma[0]->object;
	zfs_vmobject_wlock(object);
	obj_size = object->un_pager.vnp.vnp_size;
	zfs_vmobject_wunlock(object);
	if (IDX_TO_OFF(ma[count - 1]->pindex) >= obj_size) {
		rangelock_exit(lr);
		ZFS_EXIT(zfsvfs);
		return (zfs_vm_pagerret_bad);
	}

	pgsin_b = 0;
	if (rbehind != NULL) {
		pgsin_b = OFF_TO_IDX(start - rounddown(start, blksz));
		pgsin_b = MIN(*rbehind, pgsin_b);
	}

	pgsin_a = 0;
	if (rahead != NULL) {
		pgsin_a = OFF_TO_IDX(roundup(end, blksz) - end);
		if (end + IDX_TO_OFF(pgsin_a) >= obj_size)
			pgsin_a = OFF_TO_IDX(round_page(obj_size) - end);
		pgsin_a = MIN(*rahead, pgsin_a);
	}

	/*
	 * NB: we need to pass the exact byte size of the data that we expect
	 * to read after accounting for the file size.  This is required because
	 * ZFS will panic if we request DMU to read beyond the end of the last
	 * allocated block.
	 */
	error = dmu_read_pages(os, zp->z_id, ma, count, &pgsin_b, &pgsin_a,
	    MIN(end, obj_size) - (end - PAGE_SIZE));

	rangelock_exit(lr);
	ZFS_ACCESSTIME_STAMP(zfsvfs, zp);
	ZFS_EXIT(zfsvfs);

	if (error != 0)
		return (zfs_vm_pagerret_error);

	VM_CNT_INC(v_vnodein);
	VM_CNT_ADD(v_vnodepgsin, count + pgsin_b + pgsin_a);
	if (rbehind != NULL)
		*rbehind = pgsin_b;
	if (rahead != NULL)
		*rahead = pgsin_a;
	return (zfs_vm_pagerret_ok);
}