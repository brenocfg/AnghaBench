#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  os_lock; int /*<<< orphan*/  os_dnodes; } ;
typedef  TYPE_1__ objset_t ;
typedef  int /*<<< orphan*/  dnode_t ;

/* Variables and functions */
 int /*<<< orphan*/ * DMU_GROUPUSED_DNODE (TYPE_1__*) ; 
 int /*<<< orphan*/ * DMU_META_DNODE (TYPE_1__*) ; 
 int /*<<< orphan*/ * DMU_USERUSED_DNODE (TYPE_1__*) ; 
 int /*<<< orphan*/  FTAG ; 
 scalar_t__ dnode_add_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dnode_evict_dbufs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dnode_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_insert_after (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
dmu_objset_evict_dbufs(objset_t *os)
{
	dnode_t dn_marker;
	dnode_t *dn;

	mutex_enter(&os->os_lock);
	dn = list_head(&os->os_dnodes);
	while (dn != NULL) {
		/*
		 * Skip dnodes without holds.  We have to do this dance
		 * because dnode_add_ref() only works if there is already a
		 * hold.  If the dnode has no holds, then it has no dbufs.
		 */
		if (dnode_add_ref(dn, FTAG)) {
			list_insert_after(&os->os_dnodes, dn, &dn_marker);
			mutex_exit(&os->os_lock);

			dnode_evict_dbufs(dn);
			dnode_rele(dn, FTAG);

			mutex_enter(&os->os_lock);
			dn = list_next(&os->os_dnodes, &dn_marker);
			list_remove(&os->os_dnodes, &dn_marker);
		} else {
			dn = list_next(&os->os_dnodes, dn);
		}
	}
	mutex_exit(&os->os_lock);

	if (DMU_USERUSED_DNODE(os) != NULL) {
		dnode_evict_dbufs(DMU_GROUPUSED_DNODE(os));
		dnode_evict_dbufs(DMU_USERUSED_DNODE(os));
	}
	dnode_evict_dbufs(DMU_META_DNODE(os));
}