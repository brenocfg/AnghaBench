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
struct TYPE_5__ {int /*<<< orphan*/ * vdev_ops; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  dva_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DTL_PARTIAL ; 
 scalar_t__ DVA_GET_GANG (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DVA_GET_OFFSET (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DVA_GET_VDEV (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  vdev_dtl_contains (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vdev_dtl_need_resilver (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  vdev_indirect_ops ; 
 TYPE_1__* vdev_lookup_top (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
dsl_scan_need_resilver(spa_t *spa, const dva_t *dva, size_t psize,
    uint64_t phys_birth)
{
	vdev_t *vd;

	vd = vdev_lookup_top(spa, DVA_GET_VDEV(dva));

	if (vd->vdev_ops == &vdev_indirect_ops) {
		/*
		 * The indirect vdev can point to multiple
		 * vdevs.  For simplicity, always create
		 * the resilver zio_t. zio_vdev_io_start()
		 * will bypass the child resilver i/o's if
		 * they are on vdevs that don't have DTL's.
		 */
		return (B_TRUE);
	}

	if (DVA_GET_GANG(dva)) {
		/*
		 * Gang members may be spread across multiple
		 * vdevs, so the best estimate we have is the
		 * scrub range, which has already been checked.
		 * XXX -- it would be better to change our
		 * allocation policy to ensure that all
		 * gang members reside on the same vdev.
		 */
		return (B_TRUE);
	}

	/*
	 * Check if the txg falls within the range which must be
	 * resilvered.  DVAs outside this range can always be skipped.
	 */
	if (!vdev_dtl_contains(vd, DTL_PARTIAL, phys_birth, 1))
		return (B_FALSE);

	/*
	 * Check if the top-level vdev must resilver this offset.
	 * When the offset does not intersect with a dirty leaf DTL
	 * then it may be possible to skip the resilver IO.  The psize
	 * is provided instead of asize to simplify the check for RAIDZ.
	 */
	if (!vdev_dtl_need_resilver(vd, DVA_GET_OFFSET(dva), psize))
		return (B_FALSE);

	return (B_TRUE);
}