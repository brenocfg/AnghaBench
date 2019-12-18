#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dnode_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DNODE_FIND_HOLE ; 
 int /*<<< orphan*/  FTAG ; 
 int dmu_object_wait_synced (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dnode_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int dnode_next_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dnode_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
dmu_offset_next(objset_t *os, uint64_t object, boolean_t hole, uint64_t *off)
{
	dnode_t *dn;
	int err;

	/*
	 * Sync any current changes before
	 * we go trundling through the block pointers.
	 */
	err = dmu_object_wait_synced(os, object);
	if (err) {
		return (err);
	}

	err = dnode_hold(os, object, FTAG, &dn);
	if (err) {
		return (err);
	}

	err = dnode_next_offset(dn, (hole ? DNODE_FIND_HOLE : 0), off, 1, 1, 0);
	dnode_rele(dn, FTAG);

	return (err);
}