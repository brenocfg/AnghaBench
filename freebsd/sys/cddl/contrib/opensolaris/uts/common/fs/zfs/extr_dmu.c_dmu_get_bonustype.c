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
struct TYPE_3__ {int /*<<< orphan*/  dn_bonustype; } ;
typedef  TYPE_1__ dnode_t ;
typedef  int /*<<< orphan*/  dmu_object_type_t ;
typedef  int /*<<< orphan*/  dmu_buf_t ;
typedef  int /*<<< orphan*/  dmu_buf_impl_t ;

/* Variables and functions */
 TYPE_1__* DB_DNODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DB_DNODE_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DB_DNODE_EXIT (int /*<<< orphan*/ *) ; 

dmu_object_type_t
dmu_get_bonustype(dmu_buf_t *db_fake)
{
	dmu_buf_impl_t *db = (dmu_buf_impl_t *)db_fake;
	dnode_t *dn;
	dmu_object_type_t type;

	DB_DNODE_ENTER(db);
	dn = DB_DNODE(db);
	type = dn->dn_bonustype;
	DB_DNODE_EXIT(db);

	return (type);
}