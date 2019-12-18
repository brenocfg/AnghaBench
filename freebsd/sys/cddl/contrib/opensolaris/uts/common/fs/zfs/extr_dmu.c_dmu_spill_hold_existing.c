#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dn_struct_rwlock; int /*<<< orphan*/  dn_have_spill; TYPE_1__* dn_objset; } ;
typedef  TYPE_2__ dnode_t ;
typedef  int /*<<< orphan*/  dmu_buf_t ;
typedef  int /*<<< orphan*/  dmu_buf_impl_t ;
struct TYPE_5__ {int /*<<< orphan*/  os_spa; } ;

/* Variables and functions */
 TYPE_2__* DB_DNODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DB_DNODE_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DB_DNODE_EXIT (int /*<<< orphan*/ *) ; 
 int DB_RF_CANFAIL ; 
 int DB_RF_HAVESTRUCT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  RW_READER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ SPA_VERSION_SA ; 
 int dmu_spill_hold_by_dnode (TYPE_2__*,int,void*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ ) ; 

int
dmu_spill_hold_existing(dmu_buf_t *bonus, void *tag, dmu_buf_t **dbp)
{
	dmu_buf_impl_t *db = (dmu_buf_impl_t *)bonus;
	dnode_t *dn;
	int err;

	DB_DNODE_ENTER(db);
	dn = DB_DNODE(db);

	if (spa_version(dn->dn_objset->os_spa) < SPA_VERSION_SA) {
		err = SET_ERROR(EINVAL);
	} else {
		rw_enter(&dn->dn_struct_rwlock, RW_READER);

		if (!dn->dn_have_spill) {
			err = SET_ERROR(ENOENT);
		} else {
			err = dmu_spill_hold_by_dnode(dn,
			    DB_RF_HAVESTRUCT | DB_RF_CANFAIL, tag, dbp);
		}

		rw_exit(&dn->dn_struct_rwlock);
	}

	DB_DNODE_EXIT(db);
	return (err);
}