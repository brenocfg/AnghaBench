#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ vdev_id; TYPE_1__* vdev_ops; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  spa_remap_cb_t ;
struct TYPE_14__ {TYPE_4__* rbca_bp; void* rbca_cb_arg; int /*<<< orphan*/  rbca_remap_offset; TYPE_2__* rbca_remap_vd; int /*<<< orphan*/  rbca_cb; } ;
typedef  TYPE_3__ remap_blkptr_cb_arg_t ;
typedef  int /*<<< orphan*/  dva_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_15__ {int /*<<< orphan*/ * blk_dva; } ;
typedef  TYPE_4__ blkptr_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* vdev_op_remap ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ;} ;

/* Variables and functions */
 scalar_t__ BP_GET_DEDUP (TYPE_4__*) ; 
 int BP_GET_NDVAS (TYPE_4__*) ; 
 scalar_t__ BP_IS_GANG (TYPE_4__*) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DVA_GET_ASIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DVA_GET_OFFSET (int /*<<< orphan*/ *) ; 
 scalar_t__ DVA_GET_VDEV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPA_FEATURE_OBSOLETE_COUNTS ; 
 int /*<<< orphan*/  remap_blkptr_cb ; 
 int /*<<< orphan*/  spa_feature_is_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_2__* vdev_lookup_top (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zfs_remap_blkptr_enable ; 

boolean_t
spa_remap_blkptr(spa_t *spa, blkptr_t *bp, spa_remap_cb_t callback, void *arg)
{
	remap_blkptr_cb_arg_t rbca;

	if (!zfs_remap_blkptr_enable)
		return (B_FALSE);

	if (!spa_feature_is_enabled(spa, SPA_FEATURE_OBSOLETE_COUNTS))
		return (B_FALSE);

	/*
	 * Dedup BP's can not be remapped, because ddt_phys_select() depends
	 * on DVA[0] being the same in the BP as in the DDT (dedup table).
	 */
	if (BP_GET_DEDUP(bp))
		return (B_FALSE);

	/*
	 * Gang blocks can not be remapped, because
	 * zio_checksum_gang_verifier() depends on the DVA[0] that's in
	 * the BP used to read the gang block header (GBH) being the same
	 * as the DVA[0] that we allocated for the GBH.
	 */
	if (BP_IS_GANG(bp))
		return (B_FALSE);

	/*
	 * Embedded BP's have no DVA to remap.
	 */
	if (BP_GET_NDVAS(bp) < 1)
		return (B_FALSE);

	/*
	 * Note: we only remap dva[0].  If we remapped other dvas, we
	 * would no longer know what their phys birth txg is.
	 */
	dva_t *dva = &bp->blk_dva[0];

	uint64_t offset = DVA_GET_OFFSET(dva);
	uint64_t size = DVA_GET_ASIZE(dva);
	vdev_t *vd = vdev_lookup_top(spa, DVA_GET_VDEV(dva));

	if (vd->vdev_ops->vdev_op_remap == NULL)
		return (B_FALSE);

	rbca.rbca_bp = bp;
	rbca.rbca_cb = callback;
	rbca.rbca_remap_vd = vd;
	rbca.rbca_remap_offset = offset;
	rbca.rbca_cb_arg = arg;

	/*
	 * remap_blkptr_cb() will be called in order for each level of
	 * indirection, until a concrete vdev is reached or a split block is
	 * encountered. old_vd and old_offset are updated within the callback
	 * as we go from the one indirect vdev to the next one (either concrete
	 * or indirect again) in that order.
	 */
	vd->vdev_ops->vdev_op_remap(vd, offset, size, remap_blkptr_cb, &rbca);

	/* Check if the DVA wasn't remapped because it is a split block */
	if (DVA_GET_VDEV(&rbca.rbca_bp->blk_dva[0]) == vd->vdev_id)
		return (B_FALSE);

	return (B_TRUE);
}