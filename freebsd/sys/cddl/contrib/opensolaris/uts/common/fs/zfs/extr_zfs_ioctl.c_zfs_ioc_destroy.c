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
struct TYPE_3__ {int /*<<< orphan*/  zc_name; int /*<<< orphan*/  zc_defer_destroy; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  scalar_t__ dmu_objset_type_t ;

/* Variables and functions */
 scalar_t__ DMU_OST_ZFS ; 
 scalar_t__ DMU_OST_ZVOL ; 
 int /*<<< orphan*/  FTAG ; 
 int dmu_objset_hold (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dmu_objset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dmu_objset_type (int /*<<< orphan*/ *) ; 
 int dsl_destroy_head (int /*<<< orphan*/ ) ; 
 int dsl_destroy_snapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  zfs_unmount_snap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_remove_minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_remove_minors (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_ioc_destroy(zfs_cmd_t *zc)
{
	objset_t *os;
	dmu_objset_type_t ost;
	int err;

	err = dmu_objset_hold(zc->zc_name, FTAG, &os);
	if (err != 0)
		return (err);
	ost = dmu_objset_type(os);
	dmu_objset_rele(os, FTAG);

	if (ost == DMU_OST_ZFS)
		zfs_unmount_snap(zc->zc_name);

	if (strchr(zc->zc_name, '@'))
		err = dsl_destroy_snapshot(zc->zc_name, zc->zc_defer_destroy);
	else
		err = dsl_destroy_head(zc->zc_name);
	if (ost == DMU_OST_ZVOL && err == 0)
#ifdef __FreeBSD__
		zvol_remove_minors(zc->zc_name);
#else
		(void) zvol_remove_minor(zc->zc_name);
#endif
	return (err);
}