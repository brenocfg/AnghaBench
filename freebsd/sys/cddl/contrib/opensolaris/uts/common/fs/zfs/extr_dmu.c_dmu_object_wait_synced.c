#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_4__ {int /*<<< orphan*/ * dn_dirty_link; } ;
typedef  TYPE_1__ dnode_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int TXG_SIZE ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ *) ; 
 int dnode_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  dnode_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ list_link_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
dmu_object_wait_synced(objset_t *os, uint64_t object)
{
	dnode_t *dn;
	int error, i;

	error = dnode_hold(os, object, FTAG, &dn);
	if (error) {
		return (error);
	}

	for (i = 0; i < TXG_SIZE; i++) {
		if (list_link_active(&dn->dn_dirty_link[i])) {
			break;
		}
	}
	dnode_rele(dn, FTAG);
	if (i != TXG_SIZE) {
		txg_wait_synced(dmu_objset_pool(os), 0);
	}

	return (0);
}