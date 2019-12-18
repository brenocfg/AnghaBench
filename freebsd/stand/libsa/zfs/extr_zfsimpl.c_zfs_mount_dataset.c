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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  spa_mos; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  objset_phys_t ;
struct TYPE_9__ {int /*<<< orphan*/  ds_bp; } ;
typedef  TYPE_2__ dsl_dataset_phys_t ;
struct TYPE_10__ {int /*<<< orphan*/  dn_bonus; } ;
typedef  TYPE_3__ dnode_phys_t ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ objset_get_dnode (TYPE_1__ const*,int /*<<< orphan*/ *,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zio_read (TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_mount_dataset(const spa_t *spa, uint64_t objnum, objset_phys_t *objset)
{
	dnode_phys_t dataset;
	dsl_dataset_phys_t *ds;

	if (objset_get_dnode(spa, &spa->spa_mos, objnum, &dataset)) {
		printf("ZFS: can't find dataset %ju\n", (uintmax_t)objnum);
		return (EIO);
	}

	ds = (dsl_dataset_phys_t *) &dataset.dn_bonus;
	if (zio_read(spa, &ds->ds_bp, objset)) {
		printf("ZFS: can't read object set for dataset %ju\n",
		    (uintmax_t)objnum);
		return (EIO);
	}

	return (0);
}