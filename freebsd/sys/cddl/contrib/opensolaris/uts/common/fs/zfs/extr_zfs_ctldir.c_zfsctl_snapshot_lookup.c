#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * z_os; } ;
typedef  TYPE_2__ zfsvfs_t ;
struct TYPE_7__ {TYPE_1__* v_vfsp; } ;
typedef  TYPE_3__ vnode_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_5__ {scalar_t__ vfs_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmu_objset_ds (int /*<<< orphan*/ *) ; 
 int dsl_dataset_snap_lookup (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfsctl_snapshot_lookup(vnode_t *vp, const char *name, uint64_t *id)
{
	objset_t *os = ((zfsvfs_t *)((vp)->v_vfsp->vfs_data))->z_os;
	int err;

	err = dsl_dataset_snap_lookup(dmu_objset_ds(os), name, id);
	return (err);
}