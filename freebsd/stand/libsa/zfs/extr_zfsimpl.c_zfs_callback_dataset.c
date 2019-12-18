#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_13__ {int /*<<< orphan*/  spa_mos; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_14__ {scalar_t__ dd_child_dir_zapobj; } ;
typedef  TYPE_2__ dsl_dir_phys_t ;
struct TYPE_15__ {scalar_t__ ds_dir_obj; } ;
typedef  TYPE_3__ dsl_dataset_phys_t ;
struct TYPE_16__ {int dn_datablkszsec; int /*<<< orphan*/  dn_bonus; } ;
typedef  TYPE_4__ dnode_phys_t ;

/* Variables and functions */
 scalar_t__ ZBT_MICRO ; 
 int dnode_read (TYPE_1__ const*,TYPE_4__*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int fzap_list (TYPE_1__ const*,TYPE_4__*,int (*) (char const*,scalar_t__)) ; 
 int mzap_list (TYPE_4__*,int (*) (char const*,scalar_t__)) ; 
 int objset_get_dnode (TYPE_1__ const*,int /*<<< orphan*/ *,scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zap_scratch ; 

int
zfs_callback_dataset(const spa_t *spa, uint64_t objnum, int (*callback)(const char *, uint64_t))
{
	uint64_t dir_obj, child_dir_zapobj, zap_type;
	dnode_phys_t child_dir_zap, dir, dataset;
	dsl_dataset_phys_t *ds;
	dsl_dir_phys_t *dd;
	int err;

	err = objset_get_dnode(spa, &spa->spa_mos, objnum, &dataset);
	if (err != 0) {
		printf("ZFS: can't find dataset %ju\n", (uintmax_t)objnum);
		return (err);
	}
	ds = (dsl_dataset_phys_t *) &dataset.dn_bonus;
	dir_obj = ds->ds_dir_obj;

	err = objset_get_dnode(spa, &spa->spa_mos, dir_obj, &dir);
	if (err != 0) {
		printf("ZFS: can't find dirobj %ju\n", (uintmax_t)dir_obj);
		return (err);
	}
	dd = (dsl_dir_phys_t *)&dir.dn_bonus;

	child_dir_zapobj = dd->dd_child_dir_zapobj;
	err = objset_get_dnode(spa, &spa->spa_mos, child_dir_zapobj, &child_dir_zap);
	if (err != 0) {
		printf("ZFS: can't find child zap %ju\n", (uintmax_t)dir_obj);
		return (err);
	}

	err = dnode_read(spa, &child_dir_zap, 0, zap_scratch, child_dir_zap.dn_datablkszsec * 512);
	if (err != 0)
		return (err);

	zap_type = *(uint64_t *) zap_scratch;
	if (zap_type == ZBT_MICRO)
		return mzap_list(&child_dir_zap, callback);
	else
		return fzap_list(spa, &child_dir_zap, callback);
}