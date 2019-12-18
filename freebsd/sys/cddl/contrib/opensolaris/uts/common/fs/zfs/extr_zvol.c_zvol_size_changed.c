#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ zv_volsize; scalar_t__ zv_volmode; struct g_provider* zv_provider; int /*<<< orphan*/  zv_minor; } ;
typedef  TYPE_1__ zvol_state_t ;
typedef  void* uint64_t ;
struct g_provider {scalar_t__ mediasize; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 scalar_t__ DDI_SUCCESS ; 
 int /*<<< orphan*/  VBLK ; 
 int /*<<< orphan*/  VCHR ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ ZFS_VOLMODE_GEOM ; 
 int /*<<< orphan*/  ddi_driver_major (int /*<<< orphan*/ ) ; 
 scalar_t__ ddi_prop_update_int64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  g_resize_provider (struct g_provider*,scalar_t__) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 void* lbtodb (void*) ; 
 int /*<<< orphan*/  makedevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spec_size_invalidate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_dip ; 

__attribute__((used)) static void
zvol_size_changed(zvol_state_t *zv, uint64_t volsize)
{
#ifdef illumos
	dev_t dev = makedevice(ddi_driver_major(zfs_dip), zv->zv_minor);

	zv->zv_volsize = volsize;
	VERIFY(ddi_prop_update_int64(dev, zfs_dip,
	    "Size", volsize) == DDI_SUCCESS);
	VERIFY(ddi_prop_update_int64(dev, zfs_dip,
	    "Nblocks", lbtodb(volsize)) == DDI_SUCCESS);

	/* Notify specfs to invalidate the cached size */
	spec_size_invalidate(dev, VBLK);
	spec_size_invalidate(dev, VCHR);
#else	/* !illumos */
	zv->zv_volsize = volsize;
	if (zv->zv_volmode == ZFS_VOLMODE_GEOM) {
		struct g_provider *pp;

		pp = zv->zv_provider;
		if (pp == NULL)
			return;
		g_topology_lock();

		/*
		 * Do not invoke resize event when initial size was zero.
		 * ZVOL initializes the size on first open, this is not
		 * real resizing.
		 */
		if (pp->mediasize == 0)
			pp->mediasize = zv->zv_volsize;
		else
			g_resize_provider(pp, zv->zv_volsize);
		g_topology_unlock();
	}
#endif	/* illumos */
}