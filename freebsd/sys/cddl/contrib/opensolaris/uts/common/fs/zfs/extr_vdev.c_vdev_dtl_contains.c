#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  vdev_dtl_lock; TYPE_1__* vdev_spa; int /*<<< orphan*/ ** vdev_dtl; } ;
typedef  TYPE_2__ vdev_t ;
typedef  size_t vdev_dtl_type_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  range_tree_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {scalar_t__ spa_load_state; TYPE_2__* spa_root_vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 size_t DTL_TYPES ; 
 scalar_t__ SPA_LOAD_NONE ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_contains (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_tree_is_empty (int /*<<< orphan*/ *) ; 

boolean_t
vdev_dtl_contains(vdev_t *vd, vdev_dtl_type_t t, uint64_t txg, uint64_t size)
{
	range_tree_t *rt = vd->vdev_dtl[t];
	boolean_t dirty = B_FALSE;

	ASSERT(t < DTL_TYPES);
	ASSERT(vd != vd->vdev_spa->spa_root_vdev);

	/*
	 * While we are loading the pool, the DTLs have not been loaded yet.
	 * Ignore the DTLs and try all devices.  This avoids a recursive
	 * mutex enter on the vdev_dtl_lock, and also makes us try hard
	 * when loading the pool (relying on the checksum to ensure that
	 * we get the right data -- note that we while loading, we are
	 * only reading the MOS, which is always checksummed).
	 */
	if (vd->vdev_spa->spa_load_state != SPA_LOAD_NONE)
		return (B_FALSE);

	mutex_enter(&vd->vdev_dtl_lock);
	if (!range_tree_is_empty(rt))
		dirty = range_tree_contains(rt, txg, size);
	mutex_exit(&vd->vdev_dtl_lock);

	return (dirty);
}