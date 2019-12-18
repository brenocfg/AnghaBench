#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_9__ {int /*<<< orphan*/  spa_mos; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  root ;
typedef  int /*<<< orphan*/  props ;
struct TYPE_10__ {scalar_t__ dd_head_dataset_obj; } ;
typedef  TYPE_2__ dsl_dir_phys_t ;
struct TYPE_11__ {int /*<<< orphan*/  dn_bonus; } ;
typedef  TYPE_3__ dnode_phys_t ;
typedef  int /*<<< orphan*/  bootfs ;

/* Variables and functions */
 scalar_t__ DMU_POOL_DIRECTORY_OBJECT ; 
 char* DMU_POOL_PROPS ; 
 char* DMU_POOL_ROOT_DATASET ; 
 int EIO ; 
 scalar_t__ objset_get_dnode (TYPE_1__ const*,int /*<<< orphan*/ *,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ zap_lookup (TYPE_1__ const*,TYPE_3__*,char*,int,int,scalar_t__*) ; 

__attribute__((used)) static int
zfs_get_root(const spa_t *spa, uint64_t *objid)
{
	dnode_phys_t dir, propdir;
	uint64_t props, bootfs, root;

	*objid = 0;

	/*
	 * Start with the MOS directory object.
	 */
	if (objset_get_dnode(spa, &spa->spa_mos, DMU_POOL_DIRECTORY_OBJECT, &dir)) {
		printf("ZFS: can't read MOS object directory\n");
		return (EIO);
	}

	/*
	 * Lookup the pool_props and see if we can find a bootfs.
	 */
	if (zap_lookup(spa, &dir, DMU_POOL_PROPS, sizeof (props), 1, &props) == 0
	     && objset_get_dnode(spa, &spa->spa_mos, props, &propdir) == 0
	     && zap_lookup(spa, &propdir, "bootfs", sizeof (bootfs), 1, &bootfs) == 0
	     && bootfs != 0)
	{
		*objid = bootfs;
		return (0);
	}
	/*
	 * Lookup the root dataset directory
	 */
	if (zap_lookup(spa, &dir, DMU_POOL_ROOT_DATASET, sizeof (root), 1, &root)
	    || objset_get_dnode(spa, &spa->spa_mos, root, &dir)) {
		printf("ZFS: can't find root dsl_dir\n");
		return (EIO);
	}

	/*
	 * Use the information from the dataset directory's bonus buffer
	 * to find the dataset object and from that the object set itself.
	 */
	dsl_dir_phys_t *dd = (dsl_dir_phys_t *) &dir.dn_bonus;
	*objid = dd->dd_head_dataset_obj;
	return (0);
}