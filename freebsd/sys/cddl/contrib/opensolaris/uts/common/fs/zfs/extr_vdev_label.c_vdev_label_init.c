#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_20__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_23__ {int vdev_children; unsigned long long vdev_crtxg; unsigned long long vdev_guid; scalar_t__ vdev_isl2cache; scalar_t__ vdev_isspare; scalar_t__ vdev_psize; int /*<<< orphan*/  vdev_notrim; int /*<<< orphan*/  vdev_guid_sum; struct TYPE_23__* vdev_parent; TYPE_1__* vdev_ops; struct TYPE_23__** vdev_child; TYPE_5__* vdev_spa; } ;
typedef  TYPE_2__ vdev_t ;
struct TYPE_24__ {char* vp_nvlist; } ;
typedef  TYPE_3__ vdev_phys_t ;
typedef  scalar_t__ vdev_labeltype_t ;
typedef  unsigned long long uint64_t ;
struct TYPE_25__ {scalar_t__ ub_txg; } ;
typedef  TYPE_4__ uberblock_t ;
struct TYPE_22__ {unsigned long long ub_txg; } ;
struct TYPE_26__ {TYPE_20__ spa_uberblock; } ;
typedef  TYPE_5__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  abd_t ;
struct TYPE_21__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EBUSY ; 
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  NV_ENCODE_XDR ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 unsigned long long POOL_STATE_L2CACHE ; 
 unsigned long long POOL_STATE_SPARE ; 
 int /*<<< orphan*/  RW_WRITER ; 
 scalar_t__ SCL_ALL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int VDEV_LABELS ; 
 scalar_t__ VDEV_LABEL_CREATE ; 
 scalar_t__ VDEV_LABEL_L2CACHE ; 
 scalar_t__ VDEV_LABEL_REMOVE ; 
 scalar_t__ VDEV_LABEL_REPLACE ; 
 scalar_t__ VDEV_LABEL_SPARE ; 
 scalar_t__ VDEV_LABEL_SPLIT ; 
 int VDEV_PAD_SIZE ; 
 scalar_t__ VDEV_SKIP_SIZE ; 
 int VDEV_UBERBLOCK_RING ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int ZIO_FLAG_CANFAIL ; 
 int ZIO_FLAG_CONFIG_WRITER ; 
 int ZIO_FLAG_TRYHARD ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CREATE_TXG ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_STATE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VERSION ; 
 int /*<<< orphan*/ * abd_alloc_for_io (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * abd_alloc_linear (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_copy_from_buf (int /*<<< orphan*/ *,TYPE_20__*,int) ; 
 int /*<<< orphan*/  abd_free (int /*<<< orphan*/ *) ; 
 void* abd_to_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abd_zero (int /*<<< orphan*/ *,int) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long long) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int nvlist_pack (int /*<<< orphan*/ *,char**,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * spa_config_generate (TYPE_5__*,TYPE_2__*,unsigned long long,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_config_held (TYPE_5__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_l2cache_add (TYPE_2__*) ; 
 scalar_t__ spa_l2cache_exists (unsigned long long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_spare_add (TYPE_2__*) ; 
 scalar_t__ spa_spare_exists (unsigned long long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long long spa_version (TYPE_5__*) ; 
 int /*<<< orphan*/  spa_writeable (TYPE_5__*) ; 
 scalar_t__ vdev_inuse (TYPE_2__*,unsigned long long,scalar_t__,unsigned long long*,unsigned long long*) ; 
 scalar_t__ vdev_is_dead (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_label_t ; 
 int /*<<< orphan*/  vdev_label_write (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ vdev_trim_on_init ; 
 int /*<<< orphan*/  vl_pad2 ; 
 int /*<<< orphan*/  vl_uberblock ; 
 int /*<<< orphan*/  vl_vdev_phys ; 
 scalar_t__ zfs_trim_enabled ; 
 int /*<<< orphan*/ * zio_root (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * zio_trim (int /*<<< orphan*/ *,TYPE_5__*,TYPE_2__*,scalar_t__,scalar_t__) ; 
 int zio_wait (int /*<<< orphan*/ *) ; 

int
vdev_label_init(vdev_t *vd, uint64_t crtxg, vdev_labeltype_t reason)
{
	spa_t *spa = vd->vdev_spa;
	nvlist_t *label;
	vdev_phys_t *vp;
	abd_t *vp_abd;
	abd_t *pad2;
	uberblock_t *ub;
	abd_t *ub_abd;
	zio_t *zio;
	char *buf;
	size_t buflen;
	int error;
	uint64_t spare_guid, l2cache_guid;
	int flags = ZIO_FLAG_CONFIG_WRITER | ZIO_FLAG_CANFAIL;

	ASSERT(spa_config_held(spa, SCL_ALL, RW_WRITER) == SCL_ALL);

	for (int c = 0; c < vd->vdev_children; c++)
		if ((error = vdev_label_init(vd->vdev_child[c],
		    crtxg, reason)) != 0)
			return (error);

	/* Track the creation time for this vdev */
	vd->vdev_crtxg = crtxg;

	if (!vd->vdev_ops->vdev_op_leaf || !spa_writeable(spa))
		return (0);

	/*
	 * Dead vdevs cannot be initialized.
	 */
	if (vdev_is_dead(vd))
		return (SET_ERROR(EIO));

	/*
	 * Determine if the vdev is in use.
	 */
	if (reason != VDEV_LABEL_REMOVE && reason != VDEV_LABEL_SPLIT &&
	    vdev_inuse(vd, crtxg, reason, &spare_guid, &l2cache_guid))
		return (SET_ERROR(EBUSY));

	/*
	 * If this is a request to add or replace a spare or l2cache device
	 * that is in use elsewhere on the system, then we must update the
	 * guid (which was initialized to a random value) to reflect the
	 * actual GUID (which is shared between multiple pools).
	 */
	if (reason != VDEV_LABEL_REMOVE && reason != VDEV_LABEL_L2CACHE &&
	    spare_guid != 0ULL) {
		uint64_t guid_delta = spare_guid - vd->vdev_guid;

		vd->vdev_guid += guid_delta;

		for (vdev_t *pvd = vd; pvd != NULL; pvd = pvd->vdev_parent)
			pvd->vdev_guid_sum += guid_delta;

		/*
		 * If this is a replacement, then we want to fallthrough to the
		 * rest of the code.  If we're adding a spare, then it's already
		 * labeled appropriately and we can just return.
		 */
		if (reason == VDEV_LABEL_SPARE)
			return (0);
		ASSERT(reason == VDEV_LABEL_REPLACE ||
		    reason == VDEV_LABEL_SPLIT);
	}

	if (reason != VDEV_LABEL_REMOVE && reason != VDEV_LABEL_SPARE &&
	    l2cache_guid != 0ULL) {
		uint64_t guid_delta = l2cache_guid - vd->vdev_guid;

		vd->vdev_guid += guid_delta;

		for (vdev_t *pvd = vd; pvd != NULL; pvd = pvd->vdev_parent)
			pvd->vdev_guid_sum += guid_delta;

		/*
		 * If this is a replacement, then we want to fallthrough to the
		 * rest of the code.  If we're adding an l2cache, then it's
		 * already labeled appropriately and we can just return.
		 */
		if (reason == VDEV_LABEL_L2CACHE)
			return (0);
		ASSERT(reason == VDEV_LABEL_REPLACE);
	}

	/*
	 * TRIM the whole thing, excluding the blank space and boot header
	 * as specified by ZFS On-Disk Specification (section 1.3), so that
	 * we start with a clean slate.
	 * It's just an optimization, so we don't care if it fails.
	 * Don't TRIM if removing so that we don't interfere with zpool
	 * disaster recovery.
	 */
	if (zfs_trim_enabled && vdev_trim_on_init && !vd->vdev_notrim && 
	    (reason == VDEV_LABEL_CREATE || reason == VDEV_LABEL_SPARE ||
	    reason == VDEV_LABEL_L2CACHE))
		zio_wait(zio_trim(NULL, spa, vd, VDEV_SKIP_SIZE,
		    vd->vdev_psize - VDEV_SKIP_SIZE));

	/*
	 * Initialize its label.
	 */
	vp_abd = abd_alloc_linear(sizeof (vdev_phys_t), B_TRUE);
	abd_zero(vp_abd, sizeof (vdev_phys_t));
	vp = abd_to_buf(vp_abd);

	/*
	 * Generate a label describing the pool and our top-level vdev.
	 * We mark it as being from txg 0 to indicate that it's not
	 * really part of an active pool just yet.  The labels will
	 * be written again with a meaningful txg by spa_sync().
	 */
	if (reason == VDEV_LABEL_SPARE ||
	    (reason == VDEV_LABEL_REMOVE && vd->vdev_isspare)) {
		/*
		 * For inactive hot spares, we generate a special label that
		 * identifies as a mutually shared hot spare.  We write the
		 * label if we are adding a hot spare, or if we are removing an
		 * active hot spare (in which case we want to revert the
		 * labels).
		 */
		VERIFY(nvlist_alloc(&label, NV_UNIQUE_NAME, KM_SLEEP) == 0);

		VERIFY(nvlist_add_uint64(label, ZPOOL_CONFIG_VERSION,
		    spa_version(spa)) == 0);
		VERIFY(nvlist_add_uint64(label, ZPOOL_CONFIG_POOL_STATE,
		    POOL_STATE_SPARE) == 0);
		VERIFY(nvlist_add_uint64(label, ZPOOL_CONFIG_GUID,
		    vd->vdev_guid) == 0);
	} else if (reason == VDEV_LABEL_L2CACHE ||
	    (reason == VDEV_LABEL_REMOVE && vd->vdev_isl2cache)) {
		/*
		 * For level 2 ARC devices, add a special label.
		 */
		VERIFY(nvlist_alloc(&label, NV_UNIQUE_NAME, KM_SLEEP) == 0);

		VERIFY(nvlist_add_uint64(label, ZPOOL_CONFIG_VERSION,
		    spa_version(spa)) == 0);
		VERIFY(nvlist_add_uint64(label, ZPOOL_CONFIG_POOL_STATE,
		    POOL_STATE_L2CACHE) == 0);
		VERIFY(nvlist_add_uint64(label, ZPOOL_CONFIG_GUID,
		    vd->vdev_guid) == 0);
	} else {
		uint64_t txg = 0ULL;

		if (reason == VDEV_LABEL_SPLIT)
			txg = spa->spa_uberblock.ub_txg;
		label = spa_config_generate(spa, vd, txg, B_FALSE);

		/*
		 * Add our creation time.  This allows us to detect multiple
		 * vdev uses as described above, and automatically expires if we
		 * fail.
		 */
		VERIFY(nvlist_add_uint64(label, ZPOOL_CONFIG_CREATE_TXG,
		    crtxg) == 0);
	}

	buf = vp->vp_nvlist;
	buflen = sizeof (vp->vp_nvlist);

	error = nvlist_pack(label, &buf, &buflen, NV_ENCODE_XDR, KM_SLEEP);
	if (error != 0) {
		nvlist_free(label);
		abd_free(vp_abd);
		/* EFAULT means nvlist_pack ran out of room */
		return (error == EFAULT ? ENAMETOOLONG : EINVAL);
	}

	/*
	 * Initialize uberblock template.
	 */
	ub_abd = abd_alloc_linear(VDEV_UBERBLOCK_RING, B_TRUE);
	abd_zero(ub_abd, VDEV_UBERBLOCK_RING);
	abd_copy_from_buf(ub_abd, &spa->spa_uberblock, sizeof (uberblock_t));
	ub = abd_to_buf(ub_abd);
	ub->ub_txg = 0;

	/* Initialize the 2nd padding area. */
	pad2 = abd_alloc_for_io(VDEV_PAD_SIZE, B_TRUE);
	abd_zero(pad2, VDEV_PAD_SIZE);

	/*
	 * Write everything in parallel.
	 */
retry:
	zio = zio_root(spa, NULL, NULL, flags);

	for (int l = 0; l < VDEV_LABELS; l++) {

		vdev_label_write(zio, vd, l, vp_abd,
		    offsetof(vdev_label_t, vl_vdev_phys),
		    sizeof (vdev_phys_t), NULL, NULL, flags);

		/*
		 * Skip the 1st padding area.
		 * Zero out the 2nd padding area where it might have
		 * left over data from previous filesystem format.
		 */
		vdev_label_write(zio, vd, l, pad2,
		    offsetof(vdev_label_t, vl_pad2),
		    VDEV_PAD_SIZE, NULL, NULL, flags);

		vdev_label_write(zio, vd, l, ub_abd,
		    offsetof(vdev_label_t, vl_uberblock),
		    VDEV_UBERBLOCK_RING, NULL, NULL, flags);
	}

	error = zio_wait(zio);

	if (error != 0 && !(flags & ZIO_FLAG_TRYHARD)) {
		flags |= ZIO_FLAG_TRYHARD;
		goto retry;
	}

	nvlist_free(label);
	abd_free(pad2);
	abd_free(ub_abd);
	abd_free(vp_abd);

	/*
	 * If this vdev hasn't been previously identified as a spare, then we
	 * mark it as such only if a) we are labeling it as a spare, or b) it
	 * exists as a spare elsewhere in the system.  Do the same for
	 * level 2 ARC devices.
	 */
	if (error == 0 && !vd->vdev_isspare &&
	    (reason == VDEV_LABEL_SPARE ||
	    spa_spare_exists(vd->vdev_guid, NULL, NULL)))
		spa_spare_add(vd);

	if (error == 0 && !vd->vdev_isl2cache &&
	    (reason == VDEV_LABEL_L2CACHE ||
	    spa_l2cache_exists(vd->vdev_guid, NULL)))
		spa_l2cache_add(vd);

	return (error);
}