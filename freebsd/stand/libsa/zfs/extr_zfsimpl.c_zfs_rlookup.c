#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {int /*<<< orphan*/  spa_mos; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_11__ {scalar_t__ dd_parent_obj; scalar_t__ dd_child_dir_zapobj; } ;
typedef  TYPE_2__ dsl_dir_phys_t ;
struct TYPE_12__ {scalar_t__ ds_dir_obj; } ;
typedef  TYPE_3__ dsl_dataset_phys_t ;
struct TYPE_13__ {int /*<<< orphan*/  dn_bonus; } ;
typedef  TYPE_4__ dnode_phys_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ objset_get_dnode (TYPE_1__ const*,int /*<<< orphan*/ *,scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ zap_rlookup (TYPE_1__ const*,TYPE_4__*,char*,scalar_t__) ; 

__attribute__((used)) static int
zfs_rlookup(const spa_t *spa, uint64_t objnum, char *result)
{
	char name[256];
	char component[256];
	uint64_t dir_obj, parent_obj, child_dir_zapobj;
	dnode_phys_t child_dir_zap, dataset, dir, parent;
	dsl_dir_phys_t *dd;
	dsl_dataset_phys_t *ds;
	char *p;
	int len;

	p = &name[sizeof(name) - 1];
	*p = '\0';

	if (objset_get_dnode(spa, &spa->spa_mos, objnum, &dataset)) {
		printf("ZFS: can't find dataset %ju\n", (uintmax_t)objnum);
		return (EIO);
	}
	ds = (dsl_dataset_phys_t *)&dataset.dn_bonus;
	dir_obj = ds->ds_dir_obj;

	for (;;) {
		if (objset_get_dnode(spa, &spa->spa_mos, dir_obj, &dir) != 0)
			return (EIO);
		dd = (dsl_dir_phys_t *)&dir.dn_bonus;

		/* Actual loop condition. */
		parent_obj  = dd->dd_parent_obj;
		if (parent_obj == 0)
			break;

		if (objset_get_dnode(spa, &spa->spa_mos, parent_obj, &parent) != 0)
			return (EIO);
		dd = (dsl_dir_phys_t *)&parent.dn_bonus;
		child_dir_zapobj = dd->dd_child_dir_zapobj;
		if (objset_get_dnode(spa, &spa->spa_mos, child_dir_zapobj, &child_dir_zap) != 0)
			return (EIO);
		if (zap_rlookup(spa, &child_dir_zap, component, dir_obj) != 0)
			return (EIO);

		len = strlen(component);
		p -= len;
		memcpy(p, component, len);
		--p;
		*p = '/';

		/* Actual loop iteration. */
		dir_obj = parent_obj;
	}

	if (*p != '\0')
		++p;
	strcpy(result, p);

	return (0);
}