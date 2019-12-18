#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_6__ {int /*<<< orphan*/  dn_struct_rwlock; TYPE_2__* dn_bonus; } ;
typedef  TYPE_1__ dnode_t ;
struct TYPE_7__ {int /*<<< orphan*/  db_mtx; } ;
typedef  TYPE_2__ dmu_buf_impl_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 scalar_t__ dnode_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  dnode_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static dmu_buf_impl_t *
dbuf_find_bonus(objset_t *os, uint64_t object)
{
	dnode_t *dn;
	dmu_buf_impl_t *db = NULL;

	if (dnode_hold(os, object, FTAG, &dn) == 0) {
		rw_enter(&dn->dn_struct_rwlock, RW_READER);
		if (dn->dn_bonus != NULL) {
			db = dn->dn_bonus;
			mutex_enter(&db->db_mtx);
		}
		rw_exit(&dn->dn_struct_rwlock);
		dnode_rele(dn, FTAG);
	}
	return (db);
}