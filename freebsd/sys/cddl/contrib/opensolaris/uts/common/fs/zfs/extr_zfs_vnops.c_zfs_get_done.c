#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* z_zfsvfs; } ;
typedef  TYPE_2__ znode_t ;
struct TYPE_10__ {int /*<<< orphan*/  zgd_lr; scalar_t__ zgd_db; TYPE_2__* zgd_private; } ;
typedef  TYPE_3__ zgd_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_8__ {int /*<<< orphan*/ * z_os; } ;

/* Variables and functions */
 int /*<<< orphan*/  VN_RELE_ASYNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZTOV (TYPE_2__*) ; 
 int /*<<< orphan*/  dmu_buf_rele (scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_vnrele_taskq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_3__*,int) ; 
 int /*<<< orphan*/  rangelock_exit (int /*<<< orphan*/ ) ; 

void
zfs_get_done(zgd_t *zgd, int error)
{
	znode_t *zp = zgd->zgd_private;
	objset_t *os = zp->z_zfsvfs->z_os;

	if (zgd->zgd_db)
		dmu_buf_rele(zgd->zgd_db, zgd);

	rangelock_exit(zgd->zgd_lr);

	/*
	 * Release the vnode asynchronously as we currently have the
	 * txg stopped from syncing.
	 */
	VN_RELE_ASYNC(ZTOV(zp), dsl_pool_vnrele_taskq(dmu_objset_pool(os)));

	kmem_free(zgd, sizeof (zgd_t));
}